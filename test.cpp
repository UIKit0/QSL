/*
 * Author: Elvis Teixeira
 *
 * This source code is in the public domain
 */

#include <QApplication>
#include <QslChartView>
#include <QslWorldView>


class World: public QslWorldView
{
public:
    
    World() : x(0.0), dx(0.01) {}
    
    double x;
    double dx;
    
    void present()
    {
        brush(Qt::red);
        pen(QPen(Qt::blue, 2));
        
        ellipse(x, 0.5, 0.2, 0.2);
        
        x += dx;
        
        if (x < 0.0) dx = -dx;
        if (x > 1.0) dx = -dx;
    }
};



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

    QslGraphPlot sinPlot("Sine", x, ys, Qt::red);
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
    
    World world;
    world.animate();

    return app.exec();
}
