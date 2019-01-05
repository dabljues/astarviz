#include "mapview.h"

// Constructors

mapview::mapview()
{
    setUpGui();
}

mapview::mapview(QWidget *parent) : QGraphicsView(parent)
{
    setUpGui();
}

// GUI setup

void mapview::setUpGui()
{
    if (scene != nullptr)
    {
        scene->clear();
        delete scene;
    }
    scene = new QGraphicsScene(this);

    this->setScene(scene);
    this->setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
}

// Events

void mapview::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;
    } else if (event->button() == Qt::RightButton) {
        removeWall(event->pos());
        scribbling = false;
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


// Drawing methods

void mapview::drawGrid(const int box_count)
{
    scene->clear();

    // Saving up parameters
    drawing_params.margin = 20.0;
    drawing_params.width = this->width();
    drawing_params.height = this->height();

    // Getting the parameters to reduce text length
    auto margin = drawing_params.margin;
    auto width = drawing_params.width;
    auto height = drawing_params.height;
    auto drawing_width = width - 2 * margin;
    auto drawing_height = height - 2 * margin;

    drawing_params.box_count = box_count;
    drawing_params.box_size = drawing_width / box_count;
    auto box_size = drawing_params.box_size;

    if (fabs(width - height) >= std::numeric_limits<double>::epsilon())
    {
        return;
    }

    bounds = Bounds(margin, margin, width - margin, height - margin);

    auto x = 0.0;
    auto y = 0.0;

    QPen pen;
    pen.setColor(Qt::black);

    // Horizontal
    for (auto i = 0; i <= box_count; i++)
    {
        QGraphicsLineItem *line = new QGraphicsLineItem(x, y, x + drawing_width, y);
        line->setPen(pen);
        scene->addItem(line);
        y += box_size;
    }

    y = 0.0;

    // Vertical
    for (auto i = 0; i <= box_count; i++)
    {
        QGraphicsLineItem *line = new QGraphicsLineItem(x, y, x, y + drawing_height);
        line->setPen(pen);
        scene->addItem(line);
        x += box_size;
    }
}

QPoint mapview::findBox(const QPointF &point)
{
    auto hbar_pos = this->horizontalScrollBar()->value();
    auto vbar_pos = this->verticalScrollBar()->value();

    auto margin = drawing_params.margin;
    auto box_size = drawing_params.box_size;
    auto scale = drawing_params.scale;

    auto x = (point.x() - margin) / scale + hbar_pos;
    auto y = (point.y() - margin) / scale + vbar_pos;

    qDebug() << "X: " << x << ", Y: " << y;

    auto x_pos = static_cast<int>(x / box_size);
    auto y_pos = static_cast<int>(y / box_size);

    x = x_pos * box_size;
    y = y_pos * box_size;

    return QPoint(x_pos, y_pos);
}

void mapview::drawBox(const QPointF &point, const QColor color)
{
    if (!bounds.inBounds(point)) return;

    auto pos = findBox(point);

    auto it = std::find(terrains.begin(), terrains.end(), pos);
    auto items = scene->items();
    if(it != terrains.end()) return;

    auto box_size = drawing_params.box_size;
    Terrain t = Terrain(pos.x() * box_size, pos.y() * box_size, box_size, box_size, pos);
    t.rect->setBrush(QBrush(color));
    t.rect->setPen(QPen());
    terrains.push_back(t);
    scene->addItem(t.rect);
}

void mapview::removeBox(const QPointF &point)
{
    if (!bounds.inBounds(point)) return;

    auto pos = findBox(point);

    auto it = std::find(terrains.begin(), terrains.end(), pos);
    if(it != terrains.end())
    {
        this->scene->removeItem(it->rect);
        terrains.erase(it);
    }
}

void mapview::drawWall(const QPointF &endPoint)
{
    drawBox(endPoint, Qt::red);
}

void mapview::removeWall(const QPointF &point)
{
    removeBox(point);
}
