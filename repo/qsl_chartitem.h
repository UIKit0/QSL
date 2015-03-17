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

#ifndef QSL_CHARTITEM_H
#define QSL_CHARTITEM_H

#include "qsl_chart.h"
#include <QGraphicsItem>

class QSL_API QslChartItem : public QGraphicsItem
{
public:

    QslChartItem();

    virtual ~QslChartItem();

    QslChart* chart() const;

    QRectF boundingRect() const;

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget);

private:

    QSL_PRIVATE_DECLS
    Q_DISABLE_COPY(QslChartItem)
};

#endif // QSL_CHARTITEM_H
