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

#ifndef QSL_PLOTABLE_H
#define QSL_PLOTABLE_H

#include "qsl_scale.h"

class QSL_API QslPlotable : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(bool visible READ visible WRITE setVisible)

public:

    QslPlotable(const QString &name = "QSL",
                QObject *parent = 0);

    virtual ~QslPlotable();

    QslScale* scale() const;

    QslChart* chart() const;

    QString name() const;

    bool visible() const;

    bool hasThumb() const;

signals:

    void appearenceChange(QslPlotable *self);

    void dataChange(QslPlotable *self);

public slots:

    void setName(const QString &name);

    void setVisible(bool visible);

protected:

    friend class QslScale;

    virtual void setScale(QslScale *scale);

    virtual void paint(QPainter *painter) = 0;

    virtual void paintThumb(const QPoint &pos, QPainter *painter);

    void setHasThumb(bool hasThumb);

private:

    QSL_PRIVATE_DECLS
    Q_DISABLE_COPY(QslPlotable)
};

#endif // QSL_PLOTABLE_H
