#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QApplication>
#include <QColor>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPen>
#include <QPoint>
#include <QScrollBar>

#include <map>
#include <vector>

#include "algorithm_utils.h"
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
    void drawVisited(const node &n);
    void drawResult(const result_path &r);
    std::vector<std::vector<bool>> get_maze();
    DrawingParameters drawing_params;

    //    std::map<QPoint, int> _terrains; Possibly switching to a map to have a const lookup time
    std::vector<Terrain> terrains;
    void setUpGui();
    void resetGui();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Bounds bounds;

    bool scribbling;
    QPoint lastPoint;
    QGraphicsScene *scene = nullptr;

    QPoint findBox(const QPointF &point);
    void drawBox(const QPointF &point, const QColor color);
    void removeBox(const QPointF &point);
    void drawWall(const QPointF &endPoint);
    void removeWall(const QPointF &point);
};

#endif  // MAPVIEW_H
