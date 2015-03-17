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

#ifndef QSL_RECTSCALE_H
#define QSL_RECTSCALE_H

#include "qsl_scale.h"
#include "qsl_rectplotable.h"
#include "qsl_rectframe.h"

class QSL_API QslRectScale : public QslScale
{
public:

    QslRectScale(const QString &name = "default",
                 QslChart *chart = 0);

    virtual ~QslRectScale();

    void add(QslRectPlotable *plot);

    void add(QslRectPlotable &plot) { add(&plot); }

    QslRectPlotable* plotable(const QString &name) const;

    QList<QslRectPlotable*> plotableList() const;

    int mapX(double x) const;
    int mapY(double y) const;

    double xMin() const;
    double xMax() const;
    double yMin() const;
    double yMax() const;
    double width() const;
    double height() const;

    int xMinPix() const;
    int xMaxPix() const;
    int yMinPix() const;
    int yMaxPix() const;
    int widthPix() const;
    int heightPix() const;

public slots:

    virtual void paint(QPainter *painter, const QRect &rect);

    virtual void update();

private:

    QSL_PRIVATE_DECLS
    Q_DISABLE_COPY(QslRectScale)
};

#endif // QSLRECTSCALE_H
