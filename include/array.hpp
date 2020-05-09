//
// Created by Piotr Brodzik on 06.05.2020.
//

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <gtest/gtest_prod.h> // add for friend test
#include <new>
#include <stdexcept>

template<class T>
class Array {
private:
    FRIEND_TEST(ArrayTest, member_variables_are_initialized);

    T *m_pData{};
    unsigned int m_nSize{};

public:
    explicit Array(unsigned int nSize) : m_nSize(nSize) {
        if (m_nSize > 0)
            m_pData = new T[m_nSize];
    }

    Array(const Array &obj) {
        m_nSize = obj.m_nSize;
        m_pData = new T[m_nSize];

        for (size_t i = 0; i < m_nSize; i++) {
            m_pData[i] = obj.m_pData[i];
        }
    }

    Array &operator=(const Array &rhs) {
        if (this == &rhs) {
            return *this;
        }
        delete[] m_pData;

        m_nSize = rhs.m_nSize;
        m_pData = new T[m_nSize];

        for (size_t i = 0; i < m_nSize; i++) {
            m_pData[i] = rhs.m_pData[i];
        }

        return *this;
    }

    virtual ~Array() {
        delete[] m_pData;
    }

    bool Set(const unsigned int &nPos, const T &Value) {
        if (!m_pData)
            throw std::bad_alloc();
        if (nPos < m_nSize) {
            m_pData[nPos] = Value;
            return true;
        } else
            return false;
    }

    T Get(const unsigned int &nPos) const {
        if (!m_pData)
            throw std::bad_alloc();
        if (nPos < m_nSize)
            return m_pData[nPos];
        else
            throw std::out_of_range("out of range");
    }

    T &operator[](const unsigned int &nPos) {
        if (!m_pData)
            throw std::bad_alloc();
        if (nPos < m_nSize)
            return m_pData[nPos];
        else
            throw std::out_of_range("out of range");
    }
};


#endif //ARRAY_HPP
