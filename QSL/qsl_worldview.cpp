
#include "qsl_worldview.h"
#include <QtGui>

class QslWorldView::Private
{
public:

    QPainter *painter;
    QBrush backBrush;

    int widthPix, heightPix;

    double xi, xf;
    double yi, yf;
    double width, height;

};


QslWorldView::QslWorldView(const QString &title,
                           int width, int height,
                           QWidget *parent) :
    QWidget(parent),
    m(new Private)
{
    m->backBrush = QBrush(Qt::white);
    setWindowTitle(title);
    resize(width,height);
    setMinimumSize(200,200);
    setXRange(0.0,1.0);
    setYRange(0.0,1.0);
}


QslWorldView::~QslWorldView()
{
    delete m;
}


void QslWorldView::setXRange(double xi, double xf)
{
    m->xi = xi;
    m->xf = xf;
    m->width = qAbs(xf - xi);
}


void QslWorldView::setYRange(double yi, double yf)
{
    m->yi = yi;
    m->yf = yf;
    m->height = qAbs(yf - yi);
}


int QslWorldView::mapX(double x) const
{
    double ret = (x - m->xi) / m->width;
    return qRound(ret*m->widthPix);
}


int QslWorldView::mapY(double y) const
{
    double ret = (y - m->yi) / m->height;
    return qRound((1.0-ret)*m->heightPix);
}


void QslWorldView::paintEvent(QPaintEvent*)
{
    m->widthPix = width();
    m->heightPix = height();

    QPainter painter(this);
    painter.fillRect(rect(),m->backBrush);

    m->painter = &painter;
    draw();
}


void QslWorldView::pen(Qt::GlobalColor c, int width)
{
    m->painter->setPen(QPen(c,width));
}


void QslWorldView::brush(Qt::GlobalColor c)
{
    m->painter->setBrush(QBrush(c));
}


void QslWorldView::line(double x1,double y1, double x2,double y2)
{
    m->painter->drawLine(mapX(x1),mapY(y1),mapX(x2),mapY(y2));
}


void QslWorldView::ellipse(double x1,double y1, int width, int height)
{
    m->painter->drawEllipse(mapX(x1)-width/2,mapY(y1)-height/2,
                            width, height);
}

