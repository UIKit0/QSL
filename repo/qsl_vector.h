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

template <typename T>
class QslVector
{
public:

    typedef T* Iterator;
    typedef const T* ConstIterator;

    QslVector();

    QslVector(qint32 n);

    QslVector(const QslVector<T> &that);

    QslVector(const QVector<T> &qVec);

    ~QslVector();

    QslVector& operator= (const QslVector<T> &that);

    qint32 size() const { return m_size; }

    T& operator[] (qint32 k) { return m_data[k]; }
    const T& operator[] (qint32 k) const { return m_data[k]; }

    void alloc(qint32 n);

    Iterator begin() { return m_data; }
    Iterator end() { return m_data + m_size; }
    ConstIterator constBegin() const { return m_data; }
    ConstIterator constEnd() const { return m_data + m_size; }

private:

    T *m_data;
    qint32 m_size;
    bool m_isView;
};


template <typename T>
inline QslVector<T>::QslVector() :
    m_data(0),
    m_size(0),
    m_isView(false) {}


template <typename T>
inline QslVector<T>::QslVector(qint32 n) :
    m_data(new T[n]),
    m_size(n),
    m_isView(false) {}


template <typename T>
inline QslVector<T>::QslVector(const QslVector<T> &that) :
    m_data(that.m_data),
    m_size(that.m_size),
    m_isView(true) {}


template <typename T>
inline QslVector<T>::QslVector(const QVector<T> &qVec) :
    m_data(const_cast<T*>(qVec.data())),
    m_size(qVec.size()),
    m_isView(true) {}


template <typename T>
inline QslVector<T>& QslVector<T>::operator= (const QslVector<T> &that)
{
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


template <typename T>
inline QslVector<T>::~QslVector()
{
    if (m_data && (m_isView==false)) {
        delete[] m_data;
    }
}


template <typename T>
inline void QslVector<T>::alloc(qint32 n)
{
   if (m_size != n || m_isView) {
       if (m_data && (m_isView==false)) {
           delete[] m_data;
       }
       m_data = new T[n];
       m_size = n;
       m_isView = false;
   }
}

#endif // QSL_VECTOR_H
