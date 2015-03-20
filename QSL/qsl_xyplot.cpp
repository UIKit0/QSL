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


QslXYPlot::QslXYPlot(const QString &name,
                     const QslVector<double> &x,
                     const QslVector<double> &y,
                     const QColor &color,
                     Scatter scatter,
                     QObject *parent) :
    QslRectPlot(name,parent),
    m(new Private)
{
    setScalable(true);
    m->scatter = scatter;
    setData(x,y);
    m->pen.setColor(color);
    m->pen.setWidth(2);
    m->antialias = true;
}


QslXYPlot::~QslXYPlot()
{
    delete m;
}


QslXYPlot::Scatter QslXYPlot::scatter() const
{
    return m->scatter;
}


void QslXYPlot::setData(const QslVector<double> &x,
                        const QslVector<double> &y)
{
    m->x = x;
    m->y = y;
    checkRanges();
    emit dataChange(this);
}


void QslXYPlot::updateData(const QslVector<double> &x,
                           const QslVector<double> &y)
{
    m->x = x;
    m->y = y;
    emit dataChange(this);
}


void QslXYPlot::setScatter(Scatter scatter)
{
    if (m->scatter != scatter) {
        m->scatter = scatter;
        emit appearenceChange(this);
    }
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
    double xi = m->x[0], xf = m->x[0];
    double yi = m->y[0], yf = m->y[0];
    for (int i=1; i<m->x.size(); i++) {
        if (m->x[i] < xi) xi = m->x[i];
        if (m->x[i] > xf) xf = m->x[i];
        if (m->y[i] < yi) yi = m->y[i];
        if (m->y[i] > yf) yf = m->y[i];
    }
    setXmin(xi);
    setXmax(xf);
    setYmin(yi);
    setYmax(yf);
}

// qslxyplot.cpp
