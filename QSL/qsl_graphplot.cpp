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

#include "qsl_graphplot.h"
#include <QtGui>

#define SYMBRAD 2
#define TWOSYMBRAD 4
#define TWOSYMBRADSQR 16


class QslGraphPlot::Private
{
public:

    QslGraphPlot::Scatter scatter;
    QslVector<double> x, y;
    QPen pen;
    QBrush brush;
    bool antialias;
};


QslGraphPlot::QslGraphPlot(const QString &name,
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
    m->brush = QBrush(color);
    m->antialias = false;
    setHasThumb(true);
}


QslGraphPlot::~QslGraphPlot()
{
    delete m;
}


QslGraphPlot::Scatter QslGraphPlot::scatter() const
{
    return m->scatter;
}


void QslGraphPlot::setPen(const QPen &pen)
{
    m->pen = pen;
    emit appearenceChange(this);
}


void QslGraphPlot::setBrush(const QBrush &brush)
{
    m->brush = brush;
    emit appearenceChange(this);
}


void QslGraphPlot::setData(const QslVector<double> &x,
                        const QslVector<double> &y)
{
    m->x = x;
    m->y = y;
    checkRanges();
    emit dataChange(this);
}


void QslGraphPlot::updateData(const QslVector<double> &x,
                           const QslVector<double> &y)
{
    m->x = x;
    m->y = y;
    emit dataChange(this);
}


void QslGraphPlot::setScatter(Scatter scatter)
{
    if (m->scatter != scatter) {
        m->scatter = scatter;
        emit appearenceChange(this);
    }
}


void QslGraphPlot::paint(QPainter *painter)
{
    switch (m->scatter) {
    case Line:
        paintLine(painter);
        break;
    case Circles:
        paintCircles(painter);
        break;
    }
}


void QslGraphPlot::paintLine(QPainter *painter)
{
    painter->setPen(m->pen);
    m->brush = Qt::NoBrush;
    painter->setBrush(Qt::NoBrush);
    painter->setRenderHint(QPainter::Antialiasing, m->antialias);
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


void QslGraphPlot::paintCircles(QPainter *painter)
{
    painter->setPen(m->pen);
    painter->setBrush(m->brush);
    painter->setRenderHint(QPainter::Antialiasing, m->antialias);
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


void QslGraphPlot::checkRanges()
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


void QslGraphPlot::paintThumb(const QPoint &pos,
                           QPainter *painter)
{
    painter->setPen(m->pen);
    painter->setBrush(m->brush);
    painter->setRenderHint(QPainter::Antialiasing, m->antialias);

    switch (m->scatter) {
    case Line:
        painter->drawLine(pos.x()-6, pos.y()-4,
                          pos.x()+6, pos.y()-4);
        painter->drawText(pos.x() + 15, pos.y(), name());
        break;
    case Circles:
        painter->drawEllipse(pos.x()-SYMBRAD, pos.y()-SYMBRAD-4,
                             TWOSYMBRAD, TWOSYMBRAD);
        painter->drawText(pos.x() + 15, pos.y(), name());
        break;
    }
}

// qslxyplot.cpp
