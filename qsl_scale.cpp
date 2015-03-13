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

#include "qsl_scale.h"
#include "qsl_chart.h"
#include "qsl_plotable.h"


class QslScale::Private
{
public:

    QString name;
    QslChart *chart;
    QList<QslPlotable*> plotables;

};


QslScale::QslScale(const QString &name,
                   QslChart *chart) :
    QObject(chart),
    m(new Private)
{
    m->name = name;
    m->chart = chart;
}


QslScale::~QslScale()
{
    delete m;
}


QString QslScale::name() const
{
    return m->name;
}


QslChart* QslScale::chart() const
{
    return m->chart;
}


void QslScale::add(QslPlotable *plot)
{
    m->plotables.append(plot);
    plot->setScale(this);
    update();
}


QslPlotable* QslScale::plotable(const QString &name) const
{
    foreach (QslPlotable *plotable, m->plotables) {
        if (plotable->name() == name) {
            return plotable;
        }
    }
    // not here
    return 0;
}


QList<QslPlotable*> QslScale::plotableList() const
{
    return m->plotables;
}


void QslScale::paint(QPainter *painter, const QRect &rect)
{
    Q_UNUSED(rect)
    foreach (QslPlotable *plotable, m->plotables) {
        if (plotable->visible()) {
            plotable->paint(painter);
        }
    }
}

