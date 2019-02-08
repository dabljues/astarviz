#ifndef DRAWING_UTILS_H
#define DRAWING_UTILS_H

#include <QGraphicsItem>
#include <QPainter>

class VisitedBox : public QGraphicsRectItem
{
public:
    VisitedBox(QGraphicsItem * parent = nullptr) : QGraphicsRectItem(parent) {}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        QGraphicsRectItem::paint(painter, option, widget);
        auto rect = boundingRect();
        auto g = QRectF(rect.x(), rect.y() + rect.height() * 3 / 4, rect.width() / 2, rect.height() / 4);
        painter->drawText(g, g_text,
                              QTextOption(Qt::AlignCenter));
        auto h = QRectF(rect.x() + rect.width() / 2, rect.y() + rect.height() * 3 / 4, rect.width() / 2, rect.height() / 4);
        painter->drawText(h, h_text,
                              QTextOption(Qt::AlignCenter));
    }
    void setText(const QString& g, const QString& h) { this->g_text = g; this->h_text = h; update(); }
    QPoint position;
private:
    QString g_text;
    QString h_text;
};

//class VisitedBox
//{
//public:
//    VisitedBox() = default;
//    VisitedBox(double x, double y, double width, double height, QPoint &pos) : pos(pos)
//    {
//        rect = new QGraphicsRectItem(x, y, width, height);
//        rect
//    }
//    bool operator==(const QPoint &p) { return p.x() == pos.x() && p.y() == pos.y(); }
//    QGraphicsRectItem *rect;
//    QPoint pos;
//};

class Terrain
{
public:
    Terrain() = default;
    Terrain(double x, double y, double width, double height, QPoint &pos) : pos(pos)
    {
        rect = new QGraphicsRectItem(x, y, width, height);
    }
    bool operator==(const QPoint &p) { return p == pos; }
    QGraphicsRectItem *rect;
    QPoint pos;
};

class Bounds
{
public:
    Bounds() = default;
    Bounds(double xleft, double yleft, double xright, double yright)
        : xleft(xleft), yleft(yleft), xright(xright), yright(yright)
    {
    }
    double xleft;
    double yleft;
    double xright;
    double yright;

    bool inBounds(const QPointF &p)
    {
        return xleft < p.x() && yleft < p.y() && xright > p.x() && yright > p.y();
    }
};

class DrawingParameters
{
public:
    DrawingParameters() : scale(1.0), hbar_pos(0), vbar_pos(0) {}
    double width;
    double height;
    double margin;
    double scale;

    int hbar_pos;
    int vbar_pos;

    double box_size;
    int box_count;
};

#endif  // DRAWING_UTILS_H
