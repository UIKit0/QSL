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

#ifndef QSL_XYAXIS_H
#define QSL_XYAXIS_H

#include "qsl_plot.h"

class QslRectScale;

class QSL_API QslXYAxis : public QslPlot
{
    Q_OBJECT
    Q_CLASSINFO("author", "Elvis M. Teixeira")

public:

    enum Component
    {
        TopAxis,
        BottomAxis,
        LeftAxis,
        RightAxis
    };


    QslXYAxis(Component component,
              const QString &name,
              QslRectScale *scale);

    ~QslXYAxis();

    Component component() const;

    void setPen(const QPen &pen);

protected:

    friend class QslRectScale;

    virtual void paint(QPainter *painter);

private:

    QSL_PRIVATE_DECLS
    Q_DISABLE_COPY(QslXYAxis)
};

#endif // QSL_XYAXIS_H
