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

#include "qsl_rectplot.h"


class QslRectPlot::Private
{
public:

    double xMin, xMax;
    double yMin, yMax;
};


QslRectPlot::QslRectPlot(const QString &name,
                         QObject *parent) :
    QslPlot(name,parent),
    m(new Private)
{}


QslRectPlot::~QslRectPlot()
{
    delete m;
}


void QslRectPlot::paintThumb(const QPoint &pos,
                             QPainter *painter)
{
    Q_UNUSED(pos)
    Q_UNUSED(painter)
}


double QslRectPlot::xMin() const { return m->xMin; }
double QslRectPlot::xMax() const { return m->xMax; }
double QslRectPlot::yMin() const { return m->yMin; }
double QslRectPlot::yMax() const { return m->yMax; }

void QslRectPlot::setXmin(double x) { m->xMin = x; }
void QslRectPlot::setXmax(double x) { m->xMax = x; }
void QslRectPlot::setYmin(double y) { m->yMin = y; }
void QslRectPlot::setYmax(double y){ m->yMax = y; }

/* qsl_rectplotable.cpp */
