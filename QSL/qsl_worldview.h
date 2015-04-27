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

#ifndef QSL_WORLDVIEW_H
#define QSL_WORLDVIEW_H

#include "qsl_vec.h"
#include <QApplication>
#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QColor>

class QSL_API QslWorldView: public QWidget
{
    Q_OBJECT
    Q_CLASSINFO("author", "Elvis M. Teixeira")

public:

    QslWorldView(const QString &title="QSL",
                 int width=600, int height=450,
                 QWidget *parent = 0);

    virtual ~QslWorldView();

    void setXRange(double xi, double xf);
    void setYRange(double yi, double yf);

    int mapX(double x) const;
    int mapY(double y) const;

    virtual void present() = 0;

    void save(const QString &fileName,
              const QSize size=QSize(600,450),
              const char *format="png");

    void animate();
    
    void pause();
    
    void setBackBrush(Qt::GlobalColor c);

    void pen(Qt::GlobalColor c, int width=1);
    
    void pen(const QPen &pen);
    
    void brush(Qt::GlobalColor c);
    
    void brush(const QBrush &brush);
    
    void line(double x1,double y1, double x2,double y2);
    
    void ellipse(double x, double y, double width, double height);
    
    void rectangle(double x, double y, double width, double height);
    
    void text(double x, double y, const QString &txt);
    
    void point(double x, double y);
    
    void antialias(bool on);

protected:

    void paintEvent(QPaintEvent *event);

private:

    QSL_PRIVATE_DECLS
    Q_DISABLE_COPY(QslWorldView)
};

#endif // QSL_WORLDVIEW_H
