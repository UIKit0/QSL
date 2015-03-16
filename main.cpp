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

#include <QtWidgets>
#include "qsl_chartwidget.h"
#include "qsl_xyplot.h"

#define N 200

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    QslVector<double> x(N), y1(N), y2(N);
    int k;
    for (k=0; k<N; k++) {
        x[k] = -5.0 + (10.0/N)*k;
        y1[k] = exp(-x[k]*x[k]);
        y2[k] = y1[k] + 0.2*y1[k]*cos(10.0*x[k]);
    }

    QslXYPlot modelPlot(x, y1, Qt::blue, QslXYPlot::Line);
    QslXYPlot samplesPlot(x, y2, Qt::red, QslXYPlot::Circles);

    QslRectScale scale;
    scale.add(modelPlot);
    scale.add(samplesPlot);

    QslChartWidget widget("QSLChart");
    widget.chart()->add(scale);
    widget.chart()->save("figure.png", QSize(400,350));
    widget.show();

    return app.exec();
}
