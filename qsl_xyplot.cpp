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

#include "qsl_xyplot.h"
#include <QtGui>

#define SYMBRAD 2
#define TWOSYMBRAD 4
#define TWOSYMBRADSQR 16


class QslXYPlot::Private
{
public:

    QslXYPlot::Scatter scatter;
    QslVector<double> x, y;
    QPen pen;
    bool antialias;
};


QslXYPlot::QslXYPlot(const QslVector<double> &x,
                     const QslVector<double> &y,
                     const QColor &color,
                     Scatter scatter) :
    m(new Private)
{
    m->scatter = scatter;
    setData(x,y);
    m->pen.setColor(color);
    m->pen.setWidthF(1.5);
    m->antialias = true;
}


QslXYPlot::~QslXYPlot()
{
    delete m;
}


void QslXYPlot::setData(const QslVector<double> &x,
                        const QslVector<double> &y)
{
    m->x = x;
    m->y = y;
    checkRanges();
}


void QslXYPlot::paint(QPainter *painter)
{
    painter->setPen(m->pen);
    painter->setRenderHint(
                QPainter::Antialiasing, m->antialias);

    switch (m->scatter) {
    case Line:
        paintLine(painter);
        break;
    case Circles:
        paintCircles(painter);
        break;
    }
}


void QslXYPlot::paintLine(QPainter *painter)
{
    QslRectScale *scale =
            static_cast<QslRectScale*>(this->scale());

    int x1 = scale->mapX(m->x[0]);
    int y1 = scale->mapY(m->y[0]);
    QPainterPath path;
    path.moveTo(x1,y1);
    for (int i=1; i<m->x.size(); i++) {
        int x2 = scale->mapX(m->x[i]);
        int y2 = scale->mapY(m->y[i]);

        int dx = x2 - x1;
        int dy = y2 - y1;
        int sqrd = dx*dx + dy*dy;

        if (sqrd > TWOSYMBRADSQR) {
            path.lineTo(x2,y2);
            x1 = x2;
            y1 = y2;
        }
    }
    painter->drawPath(path);
}


void QslXYPlot::paintCircles(QPainter *painter)
{
    QslRectScale *scale =
            static_cast<QslRectScale*>(this->scale());

    int x1 = scale->mapX(m->x[0]);
    int y1 = scale->mapY(m->y[0]);
    painter->drawEllipse(x1-SYMBRAD, y1-SYMBRAD,
                         TWOSYMBRAD, TWOSYMBRAD);
    for (int i=1; i<m->x.size(); i++) {
        int x2 = scale->mapX(m->x[i]);
        int y2 = scale->mapY(m->y[i]);

        int dx = x2 - x1;
        int dy = y2 - y1;
        int sqrd = dx*dx + dy*dy;

        if (sqrd > TWOSYMBRADSQR) {
            painter->drawEllipse(x2-SYMBRAD, y2-SYMBRAD,
                                 TWOSYMBRAD, TWOSYMBRAD);
            x1 = x2;
            y1 = y2;
        }
    }
}


void QslXYPlot::checkRanges()
{
    setXmin(m->x[0]);
    setXmax(m->x[0]);
    setYmin(m->y[0]);
    setYmax(m->y[0]);
    for (int i=1; i<m->x.size(); i++) {
        if (m->x[i] < xMin()) setXmin(m->x[i]);
        if (m->x[i] > xMax()) setXmax(m->x[i]);
        if (m->y[i] < yMin()) setYmin(m->y[i]);
        if (m->y[i] > yMax()) setYmax(m->y[i]);
    }
}

// qslxyplot.cpp
