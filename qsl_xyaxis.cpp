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

#include "qsl_xyaxis.h"
#include "qsl_rectscale.h"
#include <QtGui>


class QslXYAxis::Private
{
public:

    Private(QslXYAxis *axis) : p(axis) {}

    void setupPaint(QslRectScale *scale);
    void paintTop(QPainter *painter, QFontMetrics *fm, QslRectScale *scale);
    void paintBottom(QPainter *painter, QFontMetrics *fm, QslRectScale *scale);
    void paintLeft(QPainter *painter, QFontMetrics *fm, QslRectScale *scale);
    void paintRight(QPainter *painter, QFontMetrics *fm, QslRectScale *scale);

    QPen pen;
    Component component;
    double divSiz;
    int divNum;
    int length;

    QslXYAxis *p;
};


QslXYAxis::QslXYAxis(Component component,
                     const QString &name,
                     QslRectScale *scale) :
    QslPlot(name),
    m(new Private(this))
{
    setScale(scale);
    m->component = component;
}


QslXYAxis::~QslXYAxis()
{
    delete m;
}


QslXYAxis::Component QslXYAxis::component() const
{
    return m->component;
}


void QslXYAxis::setPen(const QPen &pen)
{
    m->pen = pen;
}


void QslXYAxis::Private::setupPaint(QslRectScale *scale)
{
    switch (component) {
    case TopAxis:
        length = scale->widthPix();
        divSiz = scale->xMax() - scale->xMin();
        divNum = length / 80;
        break;
    case BottomAxis:
        length = scale->widthPix();
        divSiz = scale->xMax() - scale->xMin();
        divNum = length / 80;
        break;
    case LeftAxis:
        length = scale->heightPix();
        divSiz = scale->yMax() - scale->yMin();
        divNum = length / 60;
        break;
    case RightAxis:
        length = scale->heightPix();
        divSiz = scale->yMax() - scale->yMin();
        divNum = length / 60;
        break;
    default:
        break;
    }
    divNum *= 5;
    divSiz /= divNum;
}


void QslXYAxis::paint(QPainter *painter)
{
    QslRectScale *scale = (QslRectScale*) this->scale();
    QFontMetrics fm = painter->fontMetrics();

    m->setupPaint(scale);
    painter->setPen(m->pen);
    painter->setRenderHint(QPainter::Antialiasing, false);

    switch (m->component) {
    case TopAxis:
        m->paintTop(painter,&fm,scale);
        break;
    case BottomAxis:
        m->paintBottom(painter,&fm,scale);
        break;
    case LeftAxis:
        m->paintLeft(painter,&fm,scale);
        break;
    case RightAxis:
        m->paintRight(painter,&fm,scale);
        break;
    default:
        break;
    }
}


void QslXYAxis::Private::paintTop(QPainter *painter,
                                  QFontMetrics *fm,
                                  QslRectScale *scale)
{
    int x = scale->xMinPix();
    int y = scale->yMinPix();
    double coord = scale->xMin();
    int txtHei = fm->height() *0.666;
    int txtWid;

    painter->drawLine(x, y, x+length, y);

    for (int k=0; k<=divNum; k++) {
        if (k%5 == 0) {
            QString numLabel = QString::number(coord,'f',2);
            txtWid = fm->width(numLabel);
            painter->drawLine(x, y, x, y+8);
            painter->drawText(x-txtWid/2, y-txtHei, numLabel);
        }
        else {
            painter->drawLine(x, y, x, y+4);
        }
        coord += divSiz;
        x = scale->mapX(coord);
    }
    txtWid = fm->width(p->name());
    x = scale->xMinPix() + (scale->widthPix() - txtWid)/2;
    y = y - 3*txtHei;
    painter->drawText(x, y, p->name());
}


void QslXYAxis::Private::paintBottom(QPainter *painter,
                                     QFontMetrics *fm,
                                     QslRectScale *scale)
{
    int x = scale->xMinPix();
    int y = scale->yMaxPix();
    double coord = scale->xMin();
    int txtHei = fm->height() *0.666;
    int txtWid;

    painter->drawLine(x, y, x+length, y);

    for (int k=0; k<=divNum; k++) {
        if (k%5 == 0) {
            QString numLabel = QString::number(coord,'f',2);
            txtWid = fm->width(numLabel);
            painter->drawLine(x, y, x, y-8);
            painter->drawText(x-txtWid/2, y+2*txtHei, numLabel);
        }
        else {
            painter->drawLine(x, y, x, y-4);
        }
        coord += divSiz;
        x = scale->mapX(coord);
    }
    txtWid = fm->width(p->name());
    x = scale->xMinPix() + (scale->widthPix() - txtWid)/2;
    y = y + 4*txtHei;
    painter->drawText(x, y, p->name());
}


void QslXYAxis::Private::paintLeft(QPainter *painter,
                                   QFontMetrics *fm,
                                   QslRectScale *scale)
{
    int x = scale->xMinPix();
    int y = scale->yMaxPix();
    double coord = scale->yMin();
    int txtHei = fm->height() *0.666;
    int txtWid;

    painter->drawLine(x, y, x, y-length);

    for (int k=0; k<=divNum; k++) {
        if (k%5 == 0) {
            QString numLabel = QString::number(coord,'f',2);
            txtWid = fm->width(numLabel);
            painter->drawLine(x, y, x+8, y);
            painter->drawText(x-txtWid-txtHei, y+txtHei/2, numLabel);
        }
        else {
            painter->drawLine(x, y, x+4, y);
        }
        coord += divSiz;
        y = scale->mapY(coord);
    }
}


void QslXYAxis::Private::paintRight(QPainter *painter,
                                    QFontMetrics *fm,
                                    QslRectScale *scale)
{
    int x = scale->xMaxPix();
    int y = scale->yMaxPix();
    double coord = scale->yMin();
    int txtHei = fm->height() *0.666;
    int txtWid;

    painter->drawLine(x, y, x, y-length);

    for (int k=0; k<=divNum; k++) {
        if (k%5 == 0) {
            QString numLabel = QString::number(coord,'f',2);
            txtWid = fm->width(numLabel);
            painter->drawLine(x, y, x-8, y);
            painter->drawText(x+txtHei, y+txtHei/2, numLabel);
        }
        else {
            painter->drawLine(x, y, x-4, y);
        }
        coord += divSiz;
        y = scale->mapY(coord);
    }
}

// qsl_xyaxis.cpp
