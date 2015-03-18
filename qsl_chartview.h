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

#ifndef QSL_CHARTWIDGET_H
#define QSL_CHARTWIDGET_H

#include <QWidget>
#include "qsl_chart.h"

// rect plots
#include "qsl_rectscale.h"
#include "qsl_xyplot.h"


class QSL_API QslChartView : public QWidget
{
    Q_OBJECT
    Q_CLASSINFO("author", "Elvis M. Teixeira")

public:

    explicit QslChartView(QWidget *parent = 0);

    QslChartView(const QString &title,
                   int width = 600, int height = 450,
                   QWidget *parent = 0);

    ~QslChartView();

    QslChart* chart() const;

public slots:

    virtual void paintEvent(QPaintEvent *event);

private:

    QSL_PRIVATE_DECLS
    Q_DISABLE_COPY(QslChartView)
};

#endif // QslChartView_H
