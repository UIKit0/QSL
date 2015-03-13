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

#include "qsl_chartitem.h"
#include <QtGui>


class QslChartItem::Private
{
public:

    QslChart chart;
    QRectF rect;
};


QslChartItem::QslChartItem() :
    m(new Private)
{
    m->rect = QRectF(0.0, 0.0, 600.0, 450.0);
}


QslChartItem::~QslChartItem()
{
    delete m;
}


QslChart* QslChartItem::chart() const
{
    return &m->chart;
}


QRectF QslChartItem::boundingRect() const
{
    return m->rect;
}


void QslChartItem::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    m->chart.paint(painter,m->rect.toRect());
}
