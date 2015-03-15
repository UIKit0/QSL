/*
 * Copyright (C) 2015  Elvis Teixeira
 *
 * This source code is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * This source code is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QSL_VECTOR_H
#define QSL_VECTOR_H

#include "qsl_global.h"

template<class T>
class QslVector
{
public:

    typedef T* Iterator;
    typedef const T* ConstIterator;

    QslVector() : m_data(0), m_size(0), m_isView(false) {}
    QslVector(int n) : m_data(new T[n]), m_size(n), m_isView(false) {}
    QslVector(const QslVector &that) : m_data(that.m_data), m_size(that.m_size), m_isView(true) {}
    QslVector(const QVector<T> &qVec) : m_data(const_cast<T*>(qVec.data())), m_size(qVec.size()), m_isView(true) {}

    QslVector& operator= (const QslVector &that) {
        if (m_data == that.m_data)
            return *this;
        if (m_data && (m_isView==false)) {
            delete[] m_data;
        }
        m_data = that.m_data;
        m_size = that.m_size;
        m_isView = true;
        return *this;
    }

    ~QslVector() {
        if (m_data && (m_isView==false)) {
            delete[] m_data;
        }
    }

    int size() const { return m_size; }

    T& operator[] (int k) { return m_data[k]; }
    const T& operator[] (int k) const { return m_data[k]; }

    Iterator begin() { return m_data; }
    Iterator end() { return m_data + m_size; }
    ConstIterator constBegin() const { return m_data; }
    ConstIterator constEnd() const { return m_data + m_size; }

private:

    T *m_data;
    int m_size;
    bool m_isView;
};

#endif // QSL_VECTOR_H
