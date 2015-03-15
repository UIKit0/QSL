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

#include "qsl_plotable.h"
#include "qsl_scale.h"
#include "qsl_chart.h"
#include <QtGui>


class QslPlotable::Private
{
public:

    QString name;
    bool visible;
    bool hasThumb;
    QslScale *scale;
};


QslPlotable::QslPlotable(const QString &name,
                         QObject *parent) :
    QObject(parent),
    m(new Private)
{
    m->scale = 0;
    m->name = name;
    m->visible = true;
    m->hasThumb = false;
}


QslPlotable::~QslPlotable()
{
    delete m;
}


QslScale* QslPlotable::scale() const
{
    return m->scale;
}


QslChart* QslPlotable::chart() const
{
    if (m->scale) {
        return m->scale->chart();
    }
    // no scale
    return 0;
}


QString QslPlotable::name() const
{
    return m->name;
}


bool QslPlotable::visible() const
{
    return m->visible;
}


bool QslPlotable::hasThumb() const
{
    return m->hasThumb;
}


void QslPlotable::setScale(QslScale *scale)
{
    QslChart *chart = this->chart();
    if (chart) {
        disconnect(this, SIGNAL(appearenceChange(QslPlotable*)),
                   chart, SLOT(onAppearenceChange(QslPlotable*)));
        disconnect(this, SIGNAL(dataChange(QslPlotable*)),
                   chart, SLOT(onDataChange(QslPlotable*)));
    }
    m->scale = scale;
    chart = this->chart();
    if (chart) {
        connect(this, SIGNAL(appearenceChange(QslPlotable*)),
                chart, SLOT(onAppearenceChange(QslPlotable*)));
        connect(this, SIGNAL(dataChange(QslPlotable*)),
                chart, SLOT(onDataChange(QslPlotable*)));
    }
}


void QslPlotable::paintThumb(const QPoint &pos,
                             QPainter *painter)
{
    Q_UNUSED(pos)
    Q_UNUSED(painter)
}


void QslPlotable::setName(const QString &name)
{
    if (m->name != name) {
        m->name = name;
        emit appearenceChange(this);
    }
}


void QslPlotable::setVisible(bool visible)
{
    if (m->visible != visible) {
        m->visible = visible;
        emit appearenceChange(this);
    }
}


void QslPlotable::setHasThumb(bool hasThumb)
{
    if (m->hasThumb != hasThumb) {
        m->hasThumb = hasThumb;
        emit appearenceChange(this);
    }
}

/* qsl_plotable.cpp */
