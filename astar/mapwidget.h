#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QPalette>
#include <QGraphicsItem>

class mapwidget : public QWidget
{
    Q_OBJECT
public:
    explicit mapwidget(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event);

    double penWidth = 2.0;
    double scale = 1.0;
    int box_count = 10;

signals:

public slots:

private:
    void set_palette();
};

#endif // MAPWIDGET_H
