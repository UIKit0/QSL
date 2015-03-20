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
#include <QtGui>


class QslScale::Private
{
public:

    QList<QslPlot*> plots;
    QString name;
    QslChart *chart;
};


QslScale::QslScale(const QString &name,
                   QslChart *chart) :
    m(new Private)
{
    m->name = name;
    m->chart = chart;
    if (chart) {
        chart->add(this);
    }
}


QslScale::~QslScale()
{
    delete m;
}


QString QslScale::name() const
{
    return m->name;
}


void QslScale::setChart(QslChart *chart)
{
    m->chart = chart;
}


QslChart* QslScale::chart() const
{
    return m->chart;
}


QslPlot* QslScale::plot(const QString &name) const
{
    foreach (QslPlot *plot, m->plots) {
        if (plot->name() == name)
            return plot;
    }
    // not found
    return 0;
}


QList<QslPlot *>& QslScale::plots()
{
    return m->plots;
}


const QList<QslPlot*>& QslScale::plots() const
{
    return m->plots;
}


void QslScale::add(QslPlot *plot)
{
    m->plots.append(plot);
    plot->setScale(this);
    update();
}


void QslScale::paint(QPainter *painter,
                     const QRect &rect)
{
    Q_UNUSED(painter)
    Q_UNUSED(rect)
}

/* qsl_scale.cpp */
