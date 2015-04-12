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

#include "qsl_chartlegend.h"
#include "qsl_chart.h"
#include "qsl_scale.h"
#include <QtGui>


class QslChartLegend::Private
{
public:

    Private(QslChartLegend *qq) :
        p(qq),
        pen(Qt::NoPen),
        brush(Qt::white) {}

    void setupDraw(QFontMetrics *fm);

    QslChartLegend *p;

    QslChart *chart;
    QPen pen;
    QBrush brush;
    QRect rect;

    int numLines;
    int posFlag;
};


QslChartLegend::QslChartLegend(QslChart *chart) :
    QslPlot(QString("scale"),chart),
    m(new Private(this))
{
    setParent(chart);
    m->chart = chart;
    m->posFlag = TopRight;
    m->rect = QRect(0,0,100,100);
#ifdef QSL_DARK_STYLE
    m->brush.setColor(Qt::black);
#endif // QSL_DARK_STYLE
}


QslChartLegend::~QslChartLegend()
{
    delete m;
}


QslChartLegend::Position QslChartLegend::positionFlag() const
{
    return (Position) m->posFlag;
}


void QslChartLegend::setPos(const QPoint &pos)
{
    m->rect.setTopLeft(pos);
}



void QslChartLegend::Private::setupDraw(QFontMetrics *fm)
{
    numLines = 0;
    int txtHei = fm->height();
    int maxTxtWidth = 0;

    const QList<QslScale*> &scaleList = chart->scales();
    foreach (QslScale *scale, scaleList) {
        const QList<QslPlot*> &plotList = scale->plots();
        foreach (QslPlot *plot, plotList) {
            if (plot->visible() && plot->hasThumb()) {
                numLines += 1;
                int txtWid = fm->width(plot->name());
                if (txtWid > maxTxtWidth)
                    maxTxtWidth = txtWid;
            }
        }
    }

    rect.setHeight((float(numLines) + 0.5) * txtHei);
    rect.setWidth(maxTxtWidth + 35);

    if (posFlag == TopRight || posFlag == BottomRight) {
        rect.translate(-rect.width(), 0);
    }
}


void QslChartLegend::paint(QPainter *painter)
{
    painter->setPen(m->pen);
    painter->setBrush(m->brush);
    painter->setRenderHint(QPainter::Antialiasing, false);

    QFontMetrics fontMetrics = painter->fontMetrics();
    m->setupDraw(&fontMetrics);

    painter->drawRect(m->rect);

    int txtHei = fontMetrics.height();
    const int x = m->rect.x() + 15;
    int y = m->rect.y();

    const QList<QslScale*> &scaleList = m->chart->scales();
    foreach (QslScale *scale, scaleList) {
        const QList<QslPlot*> &plotList = scale->plots();
        foreach (QslPlot *plot, plotList) {
            if (plot->visible() && plot->hasThumb()) {
                y += txtHei;
                plot->paintThumb(QPoint(x,y), painter);
            }
        }
    }
}

// qsl_chartlegend.cpp
