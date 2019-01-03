#ifndef ASTAR_H
#define ASTAR_H

#include <QMainWindow>
#include <QDebug>
#include <QtGui>
#include <QtCore>
#include <QPainter>
#include <QWidget>
#include <QPen>
#include <QGraphicsScene>
#include "mapwidget.h"

namespace Ui {
class astar;
}

class astar : public QMainWindow
{
    Q_OBJECT
public:
    explicit astar(QWidget *parent=nullptr);
    void drawGrid(int box_count);
    ~astar();

private:
    Ui::astar *ui;    
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;

private slots:

    void on_horizontalSlider_valueChanged(int value);
    void on_pushButton_clicked();
};

#endif // ASTAR_H
