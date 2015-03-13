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

#ifndef QSL_SCALE_H
#define QSL_SCALE_H

#include "qsl_global.h"

QT_BEGIN_NAMESPACE
class QPainter;
QT_END_NAMESPACE

class QslChart;
class QslPlotable;

class QSL_API QslScale : public QObject
{
    Q_OBJECT

public:

    QslScale(const QString &name, QslChart *chart);

    virtual ~QslScale();

    QString name() const;

    QslChart* chart() const;

    void add(QslPlotable *plot);

    QslPlotable* plotable(const QString &name) const;

    QList<QslPlotable*> plotableList() const;

    virtual void paint(QPainter *painter, const QRect &rect);

public slots:

    virtual void update() = 0;

private:

    QSL_PRIVATE_DECLS
    Q_DISABLE_COPY(QslScale)
};

#endif // QSL_SCALE_H
