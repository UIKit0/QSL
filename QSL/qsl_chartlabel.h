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

#ifndef QSL_CHARTLABEL_H
#define QSL_CHARTLABEL_H

#include "qsl_rectplot.h"
#include "qsl_rectscale.h"
#include <QColor>


class QSL_API QslChartLabel : public QslPlot
{
    Q_OBJECT
    Q_CLASSINFO("author", "Elvis M. Teixeira")
    
public:
    
    QslChartLabel(const QString &text, QObject *parent=0);
    
    ~QslChartLabel();
    
    QString text() const;
    
    void setText(const QString &text);
    
    QPen pen() const;
    
private:
    
    QSL_PRIVATE_DECLS
    Q_DISABLE_COPY(QslChartLabel)
};

#endif // QSL_CHARTLABEL_H
