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

#ifndef QSL_PLOT_H
#define QSL_PLOT_H

#include "qsl_global.h"

QT_BEGIN_NAMESPACE
class QPainter;
QT_END_NAMESPACE

class QslChart;
class QslScale;
class QslChartLegend;

class QSL_API QslPlot : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("author", "Elvis M. Teixeira")
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(bool visible READ visible WRITE setVisible)

public:

    QslPlot(const QString &name,
            QObject *parent = 0);

    virtual ~QslPlot();

    QslScale* scale() const;

    QslChart* chart() const;

    QString name() const;

    bool visible() const;

    bool hasThumb() const;

    bool scalable() const;

signals:

    void appearenceChange(QslPlot *self);

    void dataChange(QslPlot *self);

public slots:

    void setName(const QString &name);

    void setVisible(bool visible);

protected:

    friend class QslScale;

    virtual void setScale(QslScale *scale);

    virtual void paint(QPainter *painter) = 0;

    friend class QslChartLegend;

    virtual void paintThumb(const QPoint &pos,
                            QPainter *painter);

    void setHasThumb(bool hasThumb);

    void setScalable(bool scalable);

private:

    QSL_PRIVATE_DECLS
    Q_DISABLE_COPY(QslPlot)
};

#endif // QSL_PLOT_H
