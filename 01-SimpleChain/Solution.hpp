#pragma once
#include <cstddef>

namespace solution {
  template<typename _Ty>struct ChainElem {
    _Ty* data;
    ChainElem* next;
  };
  
  template<typename _Ty>class SimpleChain {
    ChainElem<_Ty>* m_Head;
    ChainElem<_Ty>* m_Tail;
    std::size_t m_Size;

    ChainElem<_Ty>* allocget() {
      if (!m_Head) {
        m_Head = new ChainElem<_Ty>();
        m_Tail = m_Head;
      }
      else {
        m_Tail->next = new ChainElem<_Ty>();
        m_Tail = m_Tail->next;
      }
      return m_Tail;
    }

    bool _chek_index(std::size_t index) {
      return index < m_Size;
    }

    ChainElem<_Ty>* _find(std::size_t index) {
      ChainElem<_Ty>* c{ m_Head };
      for (int i = 0; i < index; ++i)
        c = c->next;
      return c;
    }

  public:
    using value_type = _Ty; 

    SimpleChain() : m_Head{ nullptr }, m_Tail{ nullptr }, m_Size{ 0 } {}
    ~SimpleChain() {
      clear();
    }

    std::size_t push_back(_Ty* data) {
      allocget()->data = data;
      return m_Size++;
    }

    void remove(std::size_t index) {
      if (!_chek_index(index))
        return;
      if (--m_Size == 0) // Warn: since here size = size-1
        clear();
      else if (index == 0) {
        ChainElem<_Ty>* c = m_Head->next;
        delete m_Head;
        m_Head = c;
      }
      else {
        ChainElem<_Ty>* c{ _find(index - 1) }, * r{ c->next };
        c->next = r->next;
        if (r) // r is nullptr for last
          delete r;
      }
    }

    _Ty* at(std::size_t index) {
      if(!_chek_index(index))
        return nullptr;
      return _find(index)->data;
    }

    _Ty* first() {
      return m_Head ? m_Head->data : nullptr;
    }

    _Ty* last() {
      return m_Tail ? m_Tail->data : nullptr;
    }

    std::size_t size() {
      return m_Size;
    }

    void clear() {
      ChainElem<_Ty>* c{ m_Head }, * buf{ nullptr };
      while (c) {
        buf = c;
        c = c->next;
        delete buf;
        buf = nullptr;
      }
      m_Head = nullptr;
      m_Size = 0;
    }
  };
}