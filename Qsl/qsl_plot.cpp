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


class QslPlot::Private
{
public:

    QString name;
    bool visible;
    bool hasThumb;
    bool scalable;
    QslScale *scale;
};


QslPlot::QslPlot(const QString &name,
                 QObject *parent) :
    QObject(parent),
    m(new Private)
{
    m->scale = 0;
    m->name = name;
    m->visible = true;
    m->hasThumb = false;
    m->scalable = false;
}


QslPlot::~QslPlot()
{
    delete m;
}


QslScale* QslPlot::scale() const
{
    return m->scale;
}


QslChart* QslPlot::chart() const
{
    if (m->scale) {
        return m->scale->chart();
    }
    // no scale
    return 0;
}


QString QslPlot::name() const
{
    return m->name;
}


bool QslPlot::visible() const
{
    return m->visible;
}


bool QslPlot::hasThumb() const
{
    return m->hasThumb;
}


bool QslPlot::scalable() const
{
    return m->scalable;
}


void QslPlot::setScale(QslScale *scale)
{
    QslChart *chart = this->chart();
    if (chart) {
        disconnect(this, SIGNAL(appearenceChange(QslPlot*)),
                   chart, SLOT(onAppearenceChange(QslPlot*)));
        disconnect(this, SIGNAL(dataChange(QslPlot*)),
                   chart, SLOT(onDataChange(QslPlot*)));
    }
    m->scale = scale;
    chart = this->chart();
    if (chart) {
        connect(this, SIGNAL(appearenceChange(QslPlot*)),
                chart, SLOT(onAppearenceChange(QslPlot*)));
        connect(this, SIGNAL(dataChange(QslPlot*)),
                chart, SLOT(onDataChange(QslPlot*)));
    }
}


void QslPlot::paintThumb(const QPoint &pos,
                         QPainter *painter)
{
    Q_UNUSED(pos)
    Q_UNUSED(painter)
}


void QslPlot::setName(const QString &name)
{
    if (m->name != name) {
        m->name = name;
        emit appearenceChange(this);
    }
}


void QslPlot::setVisible(bool visible)
{
    if (m->visible != visible) {
        m->visible = visible;
        emit appearenceChange(this);
    }
}


void QslPlot::setHasThumb(bool hasThumb)
{
    m->hasThumb = hasThumb;
}


void QslPlot::setScalable(bool scalable)
{
    m->scalable = scalable;
}

/* qsl_plotable.cpp */
