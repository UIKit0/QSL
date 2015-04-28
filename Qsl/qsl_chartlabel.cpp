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

#include "qsl_chartlabel.h"


class QslChartLabel::Private
{
public:
    
    QString text;
    QPen pen;
};


QslChartLabel::QslChartLabel(const QString &text,
                             QObject *parent) :
    QslPlot(text,parent),
    m(new Private)
{
    m->text = text;
#ifdef QSL_DARK_STYLE
    m->pen.setColor(Qt::white);
#endif // QSL_DARK_STYLE
}


QslChartLabel::~QslChartLabel()
{
    delete m;
}


QString QslChartLabel::text() const
{
    return m->text;
}


void QslChartLabel::setText(const QString &text)
{
    if (m->text != text) {
        m->text = text;
        emit appearenceChange(this);
    }
}


QPen QslChartLabel::pen() const
{
    return m->pen;
}

// qsl_chartlabel.cpp
