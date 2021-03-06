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

#ifndef QSL_CHARTVIEW_H
#define QSL_CHARTVIEW_H

#include <QWidget>
#include "qsl_chart.h"


class QSL_API QslChartView : public QWidget
{
    Q_OBJECT
    Q_CLASSINFO("author", "Elvis M. Teixeira")

public:

    QslChartView(const QString &title="Qsl",
                 int width=500, int height=350,
                 QWidget *parent = 0);
    
    explicit QslChartView(QWidget *parent);

    ~QslChartView();

    QslChart* chart() const;

public slots:

    virtual void paintEvent(QPaintEvent *event);

private:

    QSL_PRIVATE_DECLS
    Q_DISABLE_COPY(QslChartView)
};

#endif // QSL_CHARTVIEW_H
