#include "mapview.h"

mapview::mapview()
{
    setUpGui();
}

mapview::mapview(QWidget *parent) : QGraphicsView(parent)
{
    setUpGui();
}

void mapview::setUpGui()
{
    scene = new QGraphicsScene(this);

    this->setScene(scene);
    this->setRenderHint(QPainter::Antialiasing);
    this->setRenderHint(QPainter::HighQualityAntialiasing);
}

void mapview::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;
    }
}

void mapview::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
    {
        drawWall(event->pos());
    }
}

void mapview::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling)
    {
        drawWall(event->pos());
        scribbling = false;
    }
}

void mapview::drawGrid(const int box_count)
{
    scene->clear();

    auto x = 0.0;
    auto y = 0.0;

    this->margin = 20.0;

    _width = this->width() - 2 * margin;
    _height = this->height() - 2 * margin;

    if (fabs(_width - _height) >= std::numeric_limits<double>::epsilon())
    {
//        qDebug() << "width (" << width <<  ") != height (" << height << ")";
        return;
    }

    this->box_count = box_count;
    this->box_size = _width / box_count;

    // Horizontal
    for (auto i = 0; i <= box_count; i++)
    {
        scene->addLine(x, y, x + _width, y);
        y += box_size;
    }

    y = 0.0;

    // Vertical
    for (auto i = 0; i <= box_count; i++)
    {
        scene->addLine(x, y, x, y + _height);
        x += box_size;
    }
}

void mapview::drawWall(const QPointF &endPoint)
{
    auto x = endPoint.x() - margin;
    auto y = endPoint.y() - margin;

    x = static_cast<int>(x / box_size) * box_size;
    y = static_cast<int>(y / box_size) * box_size;

    QGraphicsRectItem* rect = new QGraphicsRectItem(x, y, this->box_size, this->box_size);
    rect->setBrush(QBrush(Qt::red));
    scene->addItem(rect);
}
