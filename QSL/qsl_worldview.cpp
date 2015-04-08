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

#include "qsl_worldview.h"
#include <QtGui>

class QslWorldView::Private
{
public:

    QPainter painter;
    QBrush backBrush;
    QTimer timer;
    bool paused;

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
    m->paused = true;
    setWindowTitle(title);
    resize(width,height);
    setMinimumSize(200,200);
    setXRange(0.0,1.0);
    setYRange(0.0,1.0);
    connect(&m->timer, SIGNAL(timeout()), this, SLOT(repaint()));
}


QslWorldView::~QslWorldView()
{
    delete m;
}


void QslWorldView::animate()
{
    if (m->paused) {
        m->paused = false;
        show();
        m->timer.start(40);
    }
}


void QslWorldView::pause()
{
    if (m->paused == false) {
        m->paused = true;
        m->timer.stop();
    }
}


void QslWorldView::setBackBrush(Qt::GlobalColor c)
{
    m->backBrush = QBrush(c);
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


void QslWorldView::save(const QString &fileName,
                        const QSize size,
                        const char *format)
{
    QImage image(size, QImage::Format_ARGB32);
    m->painter.begin(&image);
    present();
    image.save(fileName,format);
    m->painter.end();
}


void QslWorldView::paintEvent(QPaintEvent*)
{
    m->widthPix = width();
    m->heightPix = height();
    m->painter.begin(this);
    m->painter.fillRect(rect(),m->backBrush);
    present();
    m->painter.end();
}


void QslWorldView::pen(Qt::GlobalColor c, int width)
{
    m->painter.setPen(QPen(c,width));
}


void QslWorldView::brush(Qt::GlobalColor c)
{
    m->painter.setBrush(QBrush(c));
}


void QslWorldView::line(double x1,double y1, double x2,double y2)
{
    m->painter.drawLine(mapX(x1),mapY(y1),mapX(x2),mapY(y2));
}


void QslWorldView::ellipse(double x1,double y1, double width, double height)
{
    m->painter.drawEllipse(mapX(x1)-width/2,mapY(y1)-height/2,
                            width, height);
}


void QslWorldView::rectangle(double x, double y, double width, double height)
{
    double xp = mapX(x);
    double yp = mapY(y+height);
    m->painter.drawRect(xp,yp,mapX(x+width)-xp,mapY(y)-yp);
}


void QslWorldView::text(double x, double y, const QString &txt)
{
    m->painter.drawText(mapX(x),mapY(y),txt);
}


void QslWorldView::point(double x, double y)
{
    m->painter.drawPoint(mapX(x),mapY(y));
}


void QslWorldView::antialias(bool on)
{
    m->painter.setRenderHint(QPainter::Antialiasing, on);
}

// qsl_worldview.cpp
