
#ifndef QSL_WORLDVIEW_H
#define QSL_WORLDVIEW_H

#include <QApplication>
#include <QWidget>

class QslWorldView: public QWidget
{
    Q_OBJECT

public:

    QslWorldView(const QString &title="QSL",
                 int width=600, int height=450,
                 QWidget *parent = 0);

    virtual ~QslWorldView();

    void setXRange(double xi, double xf);
    void setYRange(double yi, double yf);

    int mapX(double x) const;
    int mapY(double y) const;

    virtual void draw() = 0;

    // DRAWING METHODS
    void pen(Qt::GlobalColor c, int width=1);
    void brush(Qt::GlobalColor c);
    void line(double x1,double y1, double x2,double y2);
    void ellipse(double x1,double y1, int width, int height);

private:

    void paintEvent(QPaintEvent *event);

    class Private;
    Private *const m;
};

#endif // QSL_WORLDVIEW_H
