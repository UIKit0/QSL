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

#ifndef QSL_RECTLABEL_H
#define QSL_RECTLABEL_H

#include "qsl_rectplot.h"

class QSL_API QslRectLabel : public QslRectPlot
{
    Q_OBJECT
    Q_CLASSINFO("author", "Elvis M. Teixeira")
    
public:
    
    QslRectLabel(double x, double y,
                 const QString &text,
                 QObject *parent = 0);
    
    ~QslRectLabel();
    
    QString text() const;
    
    void setText(const QString &text);
    
    QPen pen() const;
    
protected:
    
    virtual void paint(QPainter *painter);
    
private:

    QSL_PRIVATE_DECLS
    Q_DISABLE_COPY(QslRectLabel)
};

#endif // QSL_RECTLABEL_H
