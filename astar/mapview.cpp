#include "mapview.h"

// Constructors

mapview::mapview() { setUpGui(); }

mapview::mapview(QWidget *parent) : QGraphicsView(parent) { setUpGui(); }

// GUI setup

void mapview::setUpGui()
{
    resetGui();
    scene = new QGraphicsScene(this);

    this->setScene(scene);
    this->setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing |
                         QPainter::HighQualityAntialiasing);
}

void mapview::resetGui()
{
    if (scene != nullptr)
    {
        scene->clear();
        delete scene;
    }
    terrains.clear();
}

// Events

void mapview::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        lastPoint = event->pos();
        scribbling = true;
    }
    else if (event->button() == Qt::RightButton)
    {
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
    terrains.clear();

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

void mapview::drawVisited(const node &n)
{
    auto items = scene->items();
    auto point = n.pos;
    auto box_size = drawing_params.box_size;
    VisitedBox *vb = new VisitedBox();
    vb->position = point;
    vb->setRect(point.x() * box_size, point.y() * box_size, box_size, box_size);
    vb->setBrush(QBrush(Qt::lightGray));
    vb->setPen(QPen());
    vb->setText(QString::number(n.G), QString::number(n.H));
    scene->addItem(vb);
}

QPoint mapview::findBox(const QPointF &point)
{
    auto hbar_pos = this->horizontalScrollBar()->value();
    auto vbar_pos = this->verticalScrollBar()->value();

    auto margin = drawing_params.margin;
    auto box_size = drawing_params.box_size;
    auto scale = drawing_params.scale;

    auto x = (point.x() - margin + hbar_pos) / scale;
    auto y = (point.y() - margin + vbar_pos) / scale;

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
    // If the box is already present on the screen - don't redraw it
    if (it != terrains.end()) return;
    auto items = scene->items();

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
    if (it != terrains.end())
    {
        this->scene->removeItem(it->rect);
        terrains.erase(it);
    }
}

void mapview::drawWall(const QPointF &endPoint) { drawBox(endPoint, Qt::red); }

void mapview::removeWall(const QPointF &point) { removeBox(point); }

void mapview::drawResult(const result_path &result)
{
    auto box_size = drawing_params.box_size;
    auto current = result.path.begin();
    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidthF(5.0);
    for (auto it = result.path.begin() + 1; it != result.path.end(); it++)
    {
        auto start_x = current->x() * box_size + box_size / 2;
        auto start_y = current->y() * box_size + box_size / 2;
        auto end_x = it->x() * box_size + box_size / 2;
        auto end_y = it->y() * box_size + box_size / 2;
        QGraphicsLineItem *line = new QGraphicsLineItem(start_x, start_y, end_x, end_y);
        line->setPen(pen);
        scene->addItem(line);
        current = it;
    }
}

// Misc

std::vector<std::vector<bool>> mapview::get_maze()
{
    std::vector<std::vector<bool>> result;
    result.resize(drawing_params.box_count);
    // Filling a vector with values of true (no terrains for now)
    for (auto &i : result)
    {
        i.resize(drawing_params.box_count);
        std::fill(i.begin(), i.end(), true);
    }
    // Adding the terrains from the drawing
    for (auto &t : terrains)
    {
        result[t.pos.y()][t.pos.x()] = false;
    }
    return result;
}
