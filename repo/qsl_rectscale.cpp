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

#include "qsl_rectscale.h"
#include "qsl_plotable.h"
#include <QtGui>


class QslRectScale::Private
{
public:

    QList<QslRectPlotable*> plotables;
    QslRectFrame frame;

    double xMin, xMax;
    double yMin, yMax;
    double width, height;

    int xMinPix, xMaxPix;
    int yMinPix, yMaxPix;
    int widthPix, heightPix;

    int xLowBound, xUpBound;
    int yLowBound, yUpBound;
};


QslRectScale::QslRectScale(const QString &name,
                           QslChart *chart) :
    QslScale(name,chart),
    m(new Private)
{
    m->xLowBound = m->xUpBound = 80.0;
    m->yLowBound = m->yUpBound = 60.0;
    m->frame.setScale(this);
    setFrame(&m->frame);
}


QslRectScale::~QslRectScale()
{
    delete m;
}


void QslRectScale::add(QslRectPlotable *plot)
{
    m->plotables.append(plot);
    plot->setScale(this);
    if (plot->scalable())
        update();
}


QslRectPlotable* QslRectScale::plotable(const QString &name) const
{
    foreach (QslRectPlotable *plotable, m->plotables) {
        if (plotable->name() == name) {
            return plotable;
        }
    }
    // not here
    return 0;
}


QList<QslRectPlotable *> QslRectScale::plotableList() const
{
    return m->plotables;
}


int QslRectScale::mapX(double x) const
{
    double ret = (x - m->xMin) / m->width;
    return qRound(m->xMinPix + ret*m->widthPix);
}


int QslRectScale::mapY(double y) const
{
    double ret = (y - m->yMin) / m->height;
    return qRound(m->yMaxPix - ret*m->heightPix);
}


void QslRectScale::paint(QPainter *painter, const QRect &rect)
{
    // get scene geometry
    m->xMinPix = rect.x() + m->xLowBound;
    m->yMinPix = rect.y() + m->yLowBound;
    m->xMaxPix = rect.x() + rect.width() - m->xUpBound;
    m->yMaxPix = rect.y() + rect.height() - m->yUpBound;
    m->widthPix = m->xMaxPix - m->xMinPix;
    m->heightPix = m->yMaxPix - m->yMinPix;

    // paint plotables
    painter->save();
    painter->setClipRect(m->xMinPix, m->yMinPix,
                         m->widthPix, m->heightPix);
    foreach (QslRectPlotable *plotable, m->plotables) {
        if (plotable->visible()) {
            plotable->paint(painter);
        }
    }
    painter->restore();

    // paint frame
    m->frame.paint(painter);
}


void QslRectScale::update()
{
    if (m->plotables.isEmpty()) {
        m->xMin = 0.0;
        m->xMax = 1.0;
        m->yMin = 0.0;
        m->yMax = 1.0;
        m->width = m->xMax - m->xMin;
        m->height = m->yMax - m->yMin;
        return;
    }

    QList<QslRectPlotable*>::iterator iter = m->plotables.begin();
    QList<QslRectPlotable*>::iterator end = m->plotables.end();
    QslRectPlotable *plot = (*iter++);

    while (plot->scalable() == false) {
        plot = (*iter++);
    }

    m->xMin = plot->xMin();
    m->xMax = plot->xMax();
    m->yMin = plot->yMin();
    m->yMax = plot->yMax();

    while (iter != end) {
        plot = *iter++;
        if (plot->scalable() == false) {
            continue;
        }
        if (plot->xMin() < m->xMin) m->xMin = plot->xMin();
        if (plot->xMax() > m->xMax) m->xMax = plot->xMax();
        if (plot->yMin() < m->yMin) m->yMin = plot->yMin();
        if (plot->yMax() > m->yMax) m->yMax = plot->yMax();
    }

    double xBound = (m->xMax - m->xMin) / 20.0;
    m->xMin -= xBound;
    m->xMax += xBound;

    double yBound = (m->yMax - m->yMin) / 20.0;
    m->yMin -= yBound;
    m->yMax += yBound;

    m->width = m->xMax - m->xMin;
    m->height = m->yMax - m->yMin;
}


double QslRectScale::xMin() const { return m->xMin; }
double QslRectScale::xMax() const { return m->xMax; }
double QslRectScale::yMin() const { return m->yMin; }
double QslRectScale::yMax() const { return m->yMax; }
double QslRectScale::width() const { return m->width; }
double QslRectScale::height() const { return m->height; }

int QslRectScale::xMinPix() const { return m->xMinPix; }
int QslRectScale::xMaxPix() const { return m->xMaxPix; }
int QslRectScale::yMinPix() const { return m->yMinPix; }
int QslRectScale::yMaxPix() const { return m->yMaxPix; }
int QslRectScale::widthPix() const { return m->widthPix; }
int QslRectScale::heightPix() const { return m->heightPix; }

/* qsl_rectscale.cpp */
