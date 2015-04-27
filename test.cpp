/*
 * Author: Elvis Teixeira
 *
 * This source code is in the public domain
 */

#include <QApplication>
#include <QSL/qsl_chartview.h>

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    const int N = 40;
    const double step = 2*M_PI/N;
    QVector<double> x, ys, yc;
    
    for (int k=0; k<N; k++) {
        x.append(k*step);
        ys.append(sin(x[k]));
        yc.append(cos(x[k]));
    }

    QslGraphPlot sinPlot("Sine", x, ys, Qt::red, QslGraphPlot::Circles);
    QslGraphPlot cosPlot("Cossine", x, yc, Qt::blue);

    QslRectScale scale;
    scale.axis(QslRectAxis::TopAxis)->setName("Trigonometry");
    scale.axis(QslRectAxis::LeftAxis)->setName("Amplitude");
    scale.axis(QslRectAxis::BottomAxis)->setName("Phase");

    scale.add(sinPlot);
    scale.add(cosPlot);

    QslChartView view;
    view.chart()->add(scale);
    view.show();

    return app.exec();
}

