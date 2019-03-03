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
#include "mapview.h"
#include "astar_algorithm.h"

namespace Ui {
class astar;
}

class astar : public QMainWindow
{
    Q_OBJECT
public:
    explicit astar(QWidget *parent=nullptr);
    void setUpGui();
    ~astar();

private:
    Ui::astar *ui;    
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;

private slots:
    void on_sliderZoom_valueChanged(int value);
    void on_buttonBoxCount_clicked();
    void on_buttonCalculate_clicked();
    void on_buttonResetUI_clicked();
};

#endif // ASTAR_H
