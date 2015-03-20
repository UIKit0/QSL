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

#ifndef QSL_RECTPLOT_H
#define QSL_RECTPLOT_H

#include "qsl_plot.h"

class QslRectScale;

class QSL_API QslRectPlot : public QslPlot
{
    Q_OBJECT
    Q_CLASSINFO("author", "Elvis M. Teixeira")

public:

    QslRectPlot(const QString &name,
                QObject *parent = 0);

    virtual ~QslRectPlot();

    double xMin() const;
    double xMax() const;
    double yMin() const;
    double yMax() const;

    void setXmin(double x);
    void setXmax(double x);
    void setYmin(double y);
    void setYmax(double y);

protected:

    friend class QslRectScale;

    virtual void paint(QPainter *painter) = 0;

    virtual void paintThumb(const QPoint &pos, QPainter *painter);

private:

    QSL_PRIVATE_DECLS
    Q_DISABLE_COPY(QslRectPlot)
};

#endif // QSL_RECTPLOT_H
