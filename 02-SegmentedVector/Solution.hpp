#pragma once
#include <cstdint>
#include <cstddef>
#include <cstring>

namespace solution {
  /* How it works ?
    We use 3 different arrays :
     - m_Data : the data array of arrays
     - m_Heads : an array of ptr that locate the end
      of each segment. It points the last elem
     - m_OffsetCorrecter : Which contains the correlation
      between a linear index to the index for m_Data. This
      is an encoded int with segment number and element
      in segment index.

    When at(x) is called, we use the offset correcter to
    know how to call m_Data. We call offsetcorrecter[x]
    which gave us 'k'. If 'y' is the last 8bits of k and
    'z' is the first 56bits of k, then we can call
    m_Data[y][z] because y is the segment number and z is
    the element index in segment. These are encoded via
    bit manipulation.
  */
  template<typename _Ty>class SegmentedVector {
    _Ty** m_Data;
    _Ty** m_Heads;
    // at(x) -> data[this[x] & 0xFFFFFFFFFFFFFF]
    // 63-56: 8bits segment number
    // 55-0: 56bits index
    std::size_t* m_OffsetCorrecter;

    std::size_t m_SegmentSize;
    std::size_t m_SegmentCount;
    std::size_t m_CurrentSegment;

    std::size_t m_Size;

    // Is true when no space is left at
    // the end of us... Vector should be packed to
    // give space back
    bool m_IsLinearlyFull;

    template<typename _Ty2>static void _reoffcorr(_Ty2** ptr, std::size_t newSize, std::size_t oldLength, std::size_t newLength) {
      if (!ptr) return;
      _Ty2* optr = *ptr;
      *ptr = new _Ty2[newLength];
      for (std::size_t i{ 0U }; i < newLength; ++i) 
        (*ptr)[i] = static_cast<std::uint64_t>(i / newSize) << 56 | i % newSize;
      if(optr)
        delete optr;
    }

  public:
    void reorganize(std::size_t nwSegSz, std::size_t nwSegCnt) {
      _Ty** oldData = m_Data;
      _Ty** oldHeads = m_Heads;
      m_Data = new _Ty*[nwSegCnt];
      m_Data[0] = new _Ty[nwSegSz];
      m_Heads = new _Ty*[nwSegCnt];
     
      // We extend if needed the offset correcter to be able
      // to support the new segment count
      const std::size_t oOffCorSz = m_SegmentCount * m_SegmentSize, nOffCorSz = nwSegCnt * nwSegCnt;
      if (nOffCorSz > oOffCorSz)
        _reoffcorr(&m_OffsetCorrecter, nwSegSz, oOffCorSz, nOffCorSz);

      // If no previous data (constructor), no copy
      if (oldData) {

        // Now we want to copy old data to new structures
        std::size_t iOldSeg{ 0U }, iNewSeg{ 0U }, iNewElem{ 0U };
        // We skip the beggining of data if empty
        // Could be simplified by including the incrementation in the while
        // condition but this version is clearer for other devs ;)
        while (iOldSeg < m_SegmentCount && !oldData[iOldSeg]) { ++iOldSeg; }
        // if we have data
        if (iOldSeg < m_SegmentCount) {
          // This notation can be simplified _Ty* oldDataIt{oldData[iOldSeg]};
          // but this version is clearer for other devs too
          _Ty* oldDataIt{ &oldData[iOldSeg][0] };
          while (iOldSeg < m_SegmentCount && oldDataIt) {
            // If we are at the end of the segment, go to next
            if (oldDataIt == oldHeads[iOldSeg]) {
              oldDataIt = &oldData[++iOldSeg][0];
              continue;
            }
            // Could be optimized : this write is not necessary
            // all the time but only for last element
            m_Heads[iNewSeg] = &m_Data[iNewSeg][iNewElem];
            // Data copy
            m_Data[iNewSeg][iNewElem++] = *oldDataIt++;
            // If segment is now full, use next one
            if (iNewElem == nwSegSz) {
              iNewElem = 0;
              m_Data[++iNewSeg] = new _Ty[nwSegSz];
            }
            // If no more segments, stop copy
            if (iNewSeg == nwSegCnt)
              break;
          }
        }

        for (std::size_t i{ 0 }; i < m_CurrentSegment; ++i)
          delete[] oldData[i];
        delete[] oldData;
        delete[] oldHeads;
        m_CurrentSegment = iNewSeg;
      }
      m_SegmentCount = nwSegCnt;
      m_SegmentSize = nwSegSz;
    }
  public:
    static_assert(!std::is_same_v<_Ty, void>, "Void cannot be used as a value_type in a container !!!");

    SegmentedVector(std::size_t segmentSize = 32U, std::size_t segmentCount = 32U) : 
      m_SegmentSize{ 0U }, m_SegmentCount{ 0U }, m_CurrentSegment{ 0U },
      m_Data{ nullptr }, m_Heads{ nullptr }, m_OffsetCorrecter{ nullptr } {
      reorganize(segmentSize, segmentCount);
      m_Data[m_CurrentSegment] = new _Ty[m_SegmentSize];
      m_Heads[m_CurrentSegment] = &m_Data[m_CurrentSegment][0];
    }

    ~SegmentedVector() {
      if (m_Data) {
        for (std::size_t i{ 0 }; i < m_CurrentSegment; ++i)
          delete[] m_Data[i];
        delete[] m_Data;
        delete[] m_Heads;
      }
    }

    
    void push_back(_Ty elem) {
      if (m_IsLinearlyFull)
        return;
      
      *m_Heads[m_CurrentSegment]++ = elem;
      
      __assume(m_Heads[m_CurrentSegment] >= m_Data[m_CurrentSegment]);
      if (m_Heads[m_CurrentSegment] - m_Data[m_CurrentSegment] == m_SegmentSize) {
        ++m_CurrentSegment;
        m_Data[m_CurrentSegment] = new _Ty[m_SegmentSize];
        m_Heads[m_CurrentSegment] = &m_Data[m_CurrentSegment][0];
        if (m_CurrentSegment == m_SegmentCount)
          m_IsLinearlyFull = true;
      }
    }

    void copy(_Ty* arr, std::size_t max = static_cast<std::size_t>(-1)) {
      std::size_t seg{ 0 };
      _Ty* ptr = &m_Data[0][0];
      while (max-- && seg < m_CurrentSegment && ptr) {
        *arr++ = *ptr++;
        if (ptr > m_Heads[seg]) {
          ++seg;
          if (seg > m_CurrentSegment)
            ptr = nullptr;
          else
            ptr = &m_Data[seg][0];
        }
      }
    }

    _Ty& at(std::size_t index) {
      const std::size_t corr{ m_OffsetCorrecter[index] };
      return m_Data[(corr & (0xFFULL << 56))>>56ULL][corr & (~0ULL >> 8)];
    }

    void remove(std::size_t index) {
      const std::size_t corr{ m_OffsetCorrecter[index] },
        segI{ (corr & (0xFFULL << 56)) >> 56ULL };
      _Ty* rdPtr = m_Data[segI] + (corr & (~0ULL >> 8));
      do {
        *rdPtr = *(rdPtr+1);
      } while (++rdPtr < m_Heads[segI]);
      --m_Heads[segI];

      // Following structure can be packed in only one loop but as
      // the first one operates on a very large amount of data,
      // so we don't want to add any operation in it
      std::size_t* corrRdPtr{ &m_OffsetCorrecter[index] }, * corrEnd{ &m_OffsetCorrecter[m_SegmentCount * m_SegmentSize] };
      do {
        *corrRdPtr = *(corrRdPtr + 1);
      } while (++corrRdPtr < corrEnd);
      corrRdPtr = &m_OffsetCorrecter[index];
      while ((*corrRdPtr & (0xFFULL << 56)) >> 56ULL == segI) {
        *corrRdPtr = segI << 56 | ((*corrRdPtr & (~0ULL >> 8)) - 1);
        ++corrRdPtr; // Simpler to understand here
      };
    }

    bool is_lineary_full() {
      return m_IsLinearlyFull;
    }

  };
}