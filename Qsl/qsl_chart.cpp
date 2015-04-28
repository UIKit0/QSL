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

#include "qsl_plot.h"
#include "qsl_scale.h"
#include "qsl_chart.h"
#include "qsl_chartlegend.h"
#include <QtGui>


class QslChart::Private
{
public:

    QslChartLegend *legend;
    QslScale *legendPosManager;
    QList<QslScale*> scales;
    QFont font;
    QBrush backBrush;
    bool paintBack;
};


QslChart::QslChart(QObject *parent) :
    QObject(parent),
    m(new Private)
{
    m->legend = new QslChartLegend(this);
    m->font = QFont("Sans", 9);
    m->backBrush = QBrush(Qt::white);
    m->paintBack = true;
    m->legendPosManager = 0;
}


QslChart::~QslChart()
{
    delete m;
}


QslChartLegend* QslChart::legend() const
{
    return m->legend;
}


QslScale* QslChart::scale(const QString &name) const
{
    foreach (QslScale *scale, m->scales) {
        if (scale->name() == name)
            return scale;
    }
    // not found
    return 0;
}


QList<QslScale *>& QslChart::scales()
{
    return m->scales;
}


const QList<QslScale*>& QslChart::scales() const
{
    return m->scales;
}

void QslChart::add(QslScale *scale)
{
    m->scales.append(scale);
    scale->setChart(this);
    m->legendPosManager = scale;
    emit changed();
}


void QslChart::paint(QPainter *painter, const QRect &rect)
{
    painter->save();
    painter->setFont(m->font);
    painter->setClipRect(rect);
    if (m->paintBack) {
        painter->fillRect(rect,m->backBrush);
    }
    foreach (QslScale *scale, m->scales) {
        scale->paint(painter,rect);
    }
    if (m->legendPosManager) {
        m->legend->setPos(m->legendPosManager->legendPos());
        if (m->legend->visible()) {
            m->legend->paint(painter);
        }
    }
    painter->restore();
}


void QslChart::save(const QString &fileName,
                    const QSize &size,
                    const char *format)
{
    QImage image(size,QImage::Format_ARGB32);
    QPainter painter(&image);
    paint(&painter,QRect(QPoint(0,0),size));
    image.save(fileName,format);
}


void QslChart::onAppearenceChange(QslPlot *plotable)
{
    Q_UNUSED(plotable)
    emit changed();
}


void QslChart::onDataChange(QslPlot *plotable)
{
    plotable->scale()->update();
    emit changed();
}

/* qsl_chart.cpp */
