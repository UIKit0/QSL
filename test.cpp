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

#include <QApplication>
#include <QSL/qsl_chartview.h>
#include <QSL/qsl_worldview.h>

class World: public QslWorldView
{
public:

    World() : QslWorldView("Moving shapes") {}

    void present() {
        static double x = 0.0;
        static double step = 0.01;

        pen(Qt::blue);
        line(0,0,x,0.5);
        pen(Qt::red);
        brush(Qt::green);
        ellipse(x,0.5,40,40);
        pen(Qt::black);
        text(x,0.55,"HELLO QSL!");

        x += step;
        if (x > 1.0 || x < 0.0) step = -step;
    }
};


int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    const int N = 500;
    QslVector<double> x(N), y(N);
    int k;
    for (k=0; k<N; k++) {
        x[k] = -5.0 + (10.0/N)*k;
        double g = exp(-x[k]*x[k]);
        y[k] = g + 0.2*g*cos(10.0*x[k]);
    }

    QslXYPlot samplesPlot("Legend", x, y, Qt::red, QslXYPlot::Circles);

    QslRectScale scale;
    scale.axis(QslXYAxis::TopAxis)->setName("Noisy gaussian");
    scale.axis(QslXYAxis::LeftAxis)->setName("Intensity");
    scale.axis(QslXYAxis::BottomAxis)->setName("Phase");

    scale.add(samplesPlot);

    QslChartView chartView("QSL Chart");
    chartView.chart()->add(scale);
    chartView.chart()->save("figure.png");
    chartView.show();

    World world;
    world.animate();

    return app.exec();
}
