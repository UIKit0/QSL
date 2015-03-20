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

#ifndef QSL_XYPLOT_H
#define QSL_XYPLOT_H

#include "qsl_rectplot.h"
#include "qsl_rectscale.h"
#include "qsl_vector.h"
#include <QColor>


class QSL_API QslXYPlot : public QslRectPlot
{
    Q_OBJECT
    Q_CLASSINFO("author", "Elvis M. Teixeira")
    Q_PROPERTY(Scatter scatter READ scatter WRITE setScatter)
    Q_ENUMS(Scatter)

public:

    enum Scatter
    {
        Line,
        Circles
    };

    QslXYPlot(const QString &name,
              const QslVector<double> &x,
              const QslVector<double> &y,
              const QColor &color = Qt::blue,
              Scatter scatter = Line,
              QObject *parent = 0);


    ~QslXYPlot();

    Scatter scatter() const;


public slots:

    void setData(const QslVector<double> &x,
                 const QslVector<double> &y);

    void updateData(const QslVector<double> &x,
                    const QslVector<double> &y);

    void setScatter(Scatter scatter);

protected:

    virtual void paint(QPainter *painter);

    void paintLine(QPainter *painter);

    void paintCircles(QPainter *painter);

    void checkRanges();

private:

    QSL_PRIVATE_DECLS
    Q_DISABLE_COPY(QslXYPlot)
};

#endif // QSL_XYPLOT_H
