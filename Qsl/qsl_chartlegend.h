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

#ifndef QSL_CHARTLEGEND_H
#define QSL_CHARTLEGEND_H

#include "qsl_plot.h"

class QSL_API QslChartLegend: public QslPlot
{
    Q_OBJECT
    Q_CLASSINFO("author", "Elvis M. Teixeira")

public:

    enum Position
    {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };


    QslChartLegend(QslChart *chart);

    virtual ~QslChartLegend();

    Position positionFlag() const;

    void setPos(const QPoint &pos);
    void setPos(int x, int y) { setPos(QPoint(x,y)); }

protected:

    friend class QslChart;
    virtual void paint(QPainter *painter);

private:

    QSL_PRIVATE_DECLS
    Q_DISABLE_COPY(QslChartLegend)
};

#endif // QSL_CHARTLEGEND_H
