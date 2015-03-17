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

#include "qsl_rectframe.h"
#include "qsl_rectscale.h"
#include <QtGui>


class QslRectFrame::Private
{
public:

    void setupPaint(QslRectScale *scale);

    void paintBottomTop(QPainter *painter,
                        QFontMetrics *fm,
                        QslRectScale *scale);

    void paintLeftRight(QPainter *painter,
                        QFontMetrics *fm,
                        QslRectScale *scale);

    QPen pen;
    double verDivSiz;
    double horDivSiz;
    int visibComp;
    int verNumDiv;
    int horNumDiv;
};


QslRectFrame::QslRectFrame() :
    QslPlotable("RectFrame"),
    m(new Private)
{
    setVisible(All, true);
}


QslRectFrame::~QslRectFrame()
{
    delete m;
}


void QslRectFrame::setVisible(Component component, bool on)
{
    if (component == All) {
        if (on) {
        m->visibComp =
                TopAxis|BottomAxis|LeftAxis|
                RightAxis|Grid;
        }
        else {
            m->visibComp = 0;
        }
        return;
    }

    m->visibComp = on ? m->visibComp|component :
                        m->visibComp^component;
}


void QslRectFrame::paint(QPainter *painter)
{
    QFontMetrics fm = painter->fontMetrics();
    QslRectScale *scale =
        static_cast<QslRectScale*>(this->scale());

    m->setupPaint(scale);
    m->paintBottomTop(painter, &fm, scale);
    m->paintLeftRight(painter, &fm, scale);
}


void QslRectFrame::Private::setupPaint(QslRectScale *scale)
{
    horNumDiv = scale->widthPix() / 80;
    horDivSiz = (scale->xMax() - scale->xMin()) / horNumDiv;
    horNumDiv *= 5;
    horDivSiz /= 5.0;
    verNumDiv = scale->heightPix() / 60;
    verDivSiz = (scale->yMax() - scale->yMin()) / verNumDiv;
    verNumDiv *= 5;
    verDivSiz /= 5.0;
}


void QslRectFrame::Private::
    paintBottomTop(QPainter *painter,
                   QFontMetrics *fm,
                   QslRectScale *scale)
{
    double coord = scale->xMin();
    int x = scale->xMinPix();
    int yb = scale->yMaxPix();
    int yt = scale->yMinPix();
    int length = scale->widthPix();
    int txtHei = fm->height() *0.666;
    int txtWid;

    if (visibComp & BottomAxis) {
        painter->drawLine(x, yb, x+length, yb);
    }
    if (visibComp & TopAxis) {
        painter->drawLine(x, yt, x+length, yt);
    }

    for (int k=0; k<=horNumDiv; k++) {
        if (k%5 == 0) {
            QString numberLabel = QString::number(coord,'f',2);
            txtWid = fm->width(numberLabel);
            if (visibComp & BottomAxis) {
                painter->drawLine(x, yb, x, yb-8);
                painter->drawText(x-txtWid/2, yb+2*txtHei, numberLabel);
                if (visibComp & Grid) {
                    QPen gridPen(pen);
                    gridPen.setStyle(Qt::DashLine);
                    gridPen.setWidthF(0.4);
                    painter->save();
                    painter->setPen(gridPen);
                    painter->drawLine(x, yb, x, yt);
                    painter->restore();
                }
            }
            if (visibComp & TopAxis) {
                painter->drawLine(x, yt, x, yt+8);
                painter->drawText(x-txtWid/2, yt-txtHei, numberLabel);
            }
        }
        else {
            if (visibComp & BottomAxis) {
                painter->drawLine(x, yb, x, yb-4);
            }
            if (visibComp & TopAxis) {
                painter->drawLine(x, yt, x, yt+4);
            }
        }
        coord += horDivSiz;
        x = scale->mapX(coord);
    }
}


void QslRectFrame::Private::
    paintLeftRight(QPainter *painter,
                   QFontMetrics *fm,
                   QslRectScale *scale)
{
    double coord = scale->yMin();
    int xl = scale->xMinPix();
    int xr = scale->xMaxPix();
    int y = scale->yMaxPix();
    int length = scale->heightPix();
    int txtHei = fm->height() *0.666;
    int txtWid;

    if (visibComp & LeftAxis) {
        painter->drawLine(xl, y, xl, y-length);
    }
    if (visibComp & RightAxis) {
        painter->drawLine(xr, y, xr, y-length);
    }

    for (int k=0; k<=verNumDiv; k++) {
        if (k%5 == 0) {
            QString numberLabel = QString::number(coord,'f',2);
            txtWid = fm->width(numberLabel);
            if (visibComp & LeftAxis) {
                painter->drawLine(xl, y, xl+8, y);
                painter->drawText(xl-txtWid-txtHei, y+txtHei/2, numberLabel);
                if (visibComp & Grid) {
                    QPen gridPen(pen);
                    gridPen.setStyle(Qt::DashLine);
                    gridPen.setWidthF(0.4);
                    painter->save();
                    painter->setPen(gridPen);
                    painter->drawLine(xl, y, xr, y);
                    painter->restore();
                }
            }
            if (visibComp & RightAxis) {
                painter->drawLine(xr, y, xr-8, y);
                painter->drawText(xr+txtHei, y+txtHei/2, numberLabel);
            }
        }
        else {
            if (visibComp & LeftAxis) {
                painter->drawLine(xl, y, xl+4, y);
            }
            if (visibComp & RightAxis) {
                painter->drawLine(xr, y, xr-4, y);
            }
        }
        coord += verDivSiz;
        y = scale->mapY(coord);
    }
}

// qsl_rectframe.cpp
