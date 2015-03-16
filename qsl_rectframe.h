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

#ifndef QSL_RECTFRAME_H
#define QSL_RECTFRAME_H

#include "qsl_plotable.h"
#include "qsl_rectscale.h"


class QSL_API QslRectFrame : public QslPlotable
{
    Q_OBJECT
    Q_ENUMS(Component)

public:

    enum Component
    {
        TopAxis     = 1 << 0,
        BottomAxis  = 1 << 1,
        LeftAxis    = 1 << 2,
        RightAxis   = 1 << 3,
        Grid        = 1 << 4,
        All         = 1 << 5
    };


    QslRectFrame();

    ~QslRectFrame();


public slots:

    void setVisible(Component component, bool on);

    virtual void paint(QPainter *painter);

private:

    QSL_PRIVATE_DECLS
    Q_DISABLE_COPY(QslRectFrame)
};

#endif // QSL_RECTFRAME_H
