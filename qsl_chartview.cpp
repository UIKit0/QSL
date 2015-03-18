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

#include "qsl_chartview.h"
#include <QtWidgets>


class QslChartView::Private
{
public:

    QslChart chart;
};


QslChartView::QslChartView(QWidget *parent) :
    QWidget(parent),
    m(new Private)
{
    setMinimumSize(250,250);
}


QslChartView::QslChartView(const QString &title,
                               int width, int height,
                               QWidget *parent) :
    QWidget(parent),
    m(new Private)
{
    resize(width,height);
    setWindowTitle(title);
    setMinimumSize(250,250);
}


QslChartView::~QslChartView()
{
    delete m;
}


QslChart* QslChartView::chart() const
{
    return &m->chart;
}


void QslChartView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    m->chart.paint(&painter, rect());
}
