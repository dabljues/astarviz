#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QPen>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QPoint>

class mapview : public QGraphicsView
{
    Q_OBJECT
public:
    mapview();
    mapview(QWidget *parent = nullptr);
    void drawGrid(const int box_count);
    double box_size;
    int box_count;
protected:
    void setUpGui();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    double _width;
    double _height;
    double margin;
    bool scribbling;
    QPoint lastPoint;
    QGraphicsScene *scene;
    void drawWall(const QPointF &endPoint);
};

#endif // MAPVIEW_H
