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

#include "qsl_rectplotable.h"


class QslRectPlotable::Private
{
public:

    double xMin, xMax;
    double yMin, yMax;
};


QslRectPlotable::QslRectPlotable(const QString &name,
                                 QObject *parent) :
    QslPlotable(name,parent),
    m(new Private)
{

}


QslRectPlotable::~QslRectPlotable()
{
    delete m;
}


void QslRectPlotable::paintThumb(const QPoint &pos,
                                 QPainter *painter)
{
    Q_UNUSED(pos)
    Q_UNUSED(painter)
}


double QslRectPlotable::xMin() const { return m->xMin; }
double QslRectPlotable::xMax() const { return m->xMax; }
double QslRectPlotable::yMin() const { return m->yMin; }
double QslRectPlotable::yMax() const { return m->yMax; }

void QslRectPlotable::setXmin(double x) { m->xMin = x; }
void QslRectPlotable::setXmax(double x) { m->xMax = x; }
void QslRectPlotable::setYmin(double y) { m->yMin = y; }
void QslRectPlotable::setYmax(double y){ m->yMax = y; }

/* qsl_rectplotable.cpp */
