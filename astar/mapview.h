#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QPen>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPoint>
#include <QColor>
#include <QDebug>
#include <QScrollBar>

#include <vector>

#include "drawing_utils.h"

class mapview : public QGraphicsView
{
    Q_OBJECT
public:
    mapview();
    mapview(QWidget *parent = nullptr);
    ~mapview() override
    {
        scene->clear();
        delete scene;
    }    
    void drawGrid(const int box_count);

    DrawingParameters drawing_params;


protected:
    void setUpGui();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Bounds bounds;

    bool scribbling;
    QPoint lastPoint;
    std::vector<Terrain> terrains;

    QGraphicsScene *scene = nullptr;
    QPoint findBox(const QPointF &point);
    void drawBox(const QPointF &point, const QColor color);
    void removeBox(const QPointF &point);
    void drawWall(const QPointF &endPoint);
    void removeWall(const QPointF &point);
};

#endif // MAPVIEW_H
