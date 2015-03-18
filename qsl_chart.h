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

#ifndef QSL_CHART_H
#define QSL_CHART_H

#include "qsl_global.h"

QT_BEGIN_NAMESPACE
class QPainter;
QT_END_NAMESPACE

class QslScale;
class QslPlot;

class QSL_API QslChart : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("author", "Elvis M. Teixeira")

public:

    explicit QslChart(QObject *parent = 0);

    virtual ~QslChart();

    QslScale* scale(const QString &name) const;

    const QList<QslScale*>& scales() const;

    virtual void add(QslScale *scale);

    void add(QslScale &scale) { add(&scale); }

    virtual void paint(QPainter *painter, const QRect &rect);

signals:

    void changed();

public slots:

    void save(const QString &fileName,
              const QSize &size = QSize(600,450),
              const char *format = "png");

    virtual void onAppearenceChange(QslPlot *plotable);

    virtual void onDataChange(QslPlot *plotable);

private:

    QSL_PRIVATE_DECLS
    Q_DISABLE_COPY(QslChart)
};

#endif // QSL_CHART_H
