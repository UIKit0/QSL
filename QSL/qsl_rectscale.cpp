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
#include "qsl_rectplot.h"
#include "qsl_chart.h"
#include "qsl_chartlegend.h"
#include <QtGui>


class QslRectScale::Private
{
public:

    QList<QslXYAxis*> axis;

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
    m->axis.append( new QslXYAxis(QslXYAxis::TopAxis, "QSL Chart", this));
    m->axis.append( new QslXYAxis(QslXYAxis::BottomAxis, "X", this));
    m->axis.append( new QslXYAxis(QslXYAxis::LeftAxis, "Y", this));
    m->axis.append( new QslXYAxis(QslXYAxis::RightAxis, "", this));
    m->axis.append( new QslXYAxis(QslXYAxis::Grid, "Grid", this));
    axis(QslXYAxis::Grid)->setVisible(false);
    m->xLowBound = m->xUpBound = 80.0;
    m->yLowBound = m->yUpBound = 60.0;
    update();
}


QslRectScale::~QslRectScale()
{
    foreach (QslXYAxis *axis, m->axis) {
        delete axis;
    }
    delete m;
}


void QslRectScale::add(QslRectPlot *plot)
{
    QslScale::add(plot);
}


QslXYAxis* QslRectScale::axis(QslXYAxis::Component c) const
{
    foreach (QslXYAxis *axis, m->axis) {
        if (axis->component() == c)
            return axis;
    }
    return 0;
}


QList<QslXYAxis *>& QslRectScale::axis()
{
    return m->axis;
}


const QList<QslXYAxis*>& QslRectScale::axis() const
{
    return m->axis;
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
    foreach (QslPlot *plot, plots()) {
        QslRectPlot *rectPlot = (QslRectPlot*) plot;
        if (rectPlot->visible()) {
            rectPlot->paint(painter);
        }
    }
    painter->restore();

    // paint frame
    foreach (QslXYAxis *axis, m->axis) {
        if (axis->visible()) {
            axis->paint(painter);
        }
    }
}


void QslRectScale::update()
{
    if (plots().isEmpty()) {
        m->xMin = 0.0;
        m->xMax = 1.0;
        m->yMin = 0.0;
        m->yMax = 1.0;
        m->width = m->xMax - m->xMin;
        m->height = m->yMax - m->yMin;
        return;
    }

    QList<QslPlot*>::const_iterator iter = plots().begin();
    QList<QslPlot*>::const_iterator end = plots().end();
    QslRectPlot *plot = (QslRectPlot*) (*iter++);

    while (plot->scalable() == false) {
        plot = (QslRectPlot*) (*iter++);
    }

    m->xMin = plot->xMin();
    m->xMax = plot->xMax();
    m->yMin = plot->yMin();
    m->yMax = plot->yMax();

    while (iter != end) {
        plot = (QslRectPlot*) (*iter++);
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


QPoint QslRectScale::legendPos() const
{
    QslChartLegend *legend = chart()->legend();

    switch (legend->positionFlag()) {
    case QslChartLegend::TopLeft:
        return QPoint(m->xMinPix + 10, m->yMinPix + 10);
        break;
    case QslChartLegend::TopRight:
        return QPoint(m->xMaxPix - 10, m->yMinPix + 10);
        break;
    case QslChartLegend::BottomLeft:
        return QPoint(m->xMinPix + 10, m->yMaxPix - 10);
        break;
    case QslChartLegend::BottomRight:
        return QPoint(m->xMaxPix - 10, m->yMaxPix - 10);
        break;
    }
    return QPoint(m->xMinPix + 10, m->yMinPix + 10);
}


void QslRectScale::setXrange(double xi, double xf)
{
    m->xMin = xi;
    m->xMax = xf;
}


void QslRectScale::setYrange(double yi, double yf)
{
    m->yMin = yi;
    m->yMax = yf;
}


void QslRectScale::setXbound(int low, int up)
{
    m->xLowBound = low;
    m->xUpBound = up;
}


void QslRectScale::setYbound(int low, int up)
{
    m->yLowBound = low;
    m->yUpBound = up;
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
