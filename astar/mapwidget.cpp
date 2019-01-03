#include "mapwidget.h"

mapwidget::mapwidget(QWidget *parent) : QWidget(parent)
{

}

void mapwidget::set_palette()
{
    QPalette pal;

    // set black background
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

void mapwidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    set_palette();

    QPainter painter(this);
    QPen pen;

    auto penWidth = this->penWidth;
    pen.setWidthF(penWidth);

    painter.setPen(pen);
    painter.save();
    painter.translate(this->scale, this->scale);

    double margin = 20;
    double width = this->width() - 2 * margin;

    auto box_count = this->box_count;

    auto box_size = (width - (box_count - 1) * penWidth) / box_count;

    auto x = margin;
    auto y = box_size;

    for (auto i = 1; i <= box_count; i++)
    {
        painter.drawLine(QLineF(x, y, x + width, y));
        y += box_size + penWidth;
    }

    painter.restore();

}
