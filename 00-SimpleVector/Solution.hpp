#pragma once
#include "Utils.hpp"
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace solution {
  template<typename _Ty>class SimpleVector {
    _Ty* m_Data;
    std::size_t m_Size;
    std::size_t m_AllocatedSize;

    void _realloc(std::size_t newSize) {
      void* tmpData = m_Data;
      m_Data = new _Ty[newSize];
      if (tmpData) {
        std::memcpy(m_Data, tmpData, m_AllocatedSize*sizeof(_Ty));
        delete[] tmpData;
      }
      m_AllocatedSize = newSize;
      
    }

  public:
    static const std::uint32_t DEFAULT_SIZE = 16;

    using value_type = _Ty;

    SimpleVector(std::size_t dsize) : m_Data{ nullptr }, m_Size{ 0 } { _realloc(dsize); }
    SimpleVector() : SimpleVector(DEFAULT_SIZE) {}

    void push_back(_Ty elem) {
      if (m_Size == m_AllocatedSize)
        _realloc(static_cast<std::size_t>(utils::rtpt_32( static_cast<std::uint32_t>(m_AllocatedSize + 1))));
      m_Data[m_Size++] = elem;
    }

    std::size_t size() {
      return m_Size;
    }

    const _Ty* at(std::size_t index) {
      return &m_Data[index];
    }

    void clear() {
      std::memset(m_Data, 0, m_AllocatedSize*sizeof(_Ty));
      m_Size = 0;
    }

    ~SimpleVector() {
      if (m_Data)
        delete[] m_Data;
    }
  };
}