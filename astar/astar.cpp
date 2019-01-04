#include "astar.h"
#include "ui_astar.h"

// Constructors and destructors

astar::astar(QWidget *parent) : QMainWindow(parent), ui(new Ui::astar)
{
    ui->setupUi(this);
    this->setUpGui();
}

astar::~astar() { delete ui; }

// GUI Setup

void astar::setUpGui()
{
    this->ui->mapAreaGraphics->drawGrid(10);
    this->ui->lineEditBoxCount->setValidator(new QIntValidator());
}

// Drawing methods

void astar::drawGrid(int box_count)
{
    scene = new QGraphicsScene(this);

    auto x = 0.0;
    auto y = 0.0;

    auto margin = 20.0;

    auto width = this->ui->mapAreaGraphics->width() - 2 * margin;
    auto height = this->ui->mapAreaGraphics->height() - 2 * margin;

    if (fabs(width - height) >= std::numeric_limits<double>::epsilon())
    {
        qDebug() << "width (" << width <<  ") != height (" << height << ")";
        return;
    }

    auto box_size = width / box_count;

    // Horizontal
    for (auto i = 0; i <= box_count; i++)
    {
        scene->addLine(x, y, x + width, y);
        y += box_size;
    }

    y = 0.0;

    // Vertical
    for (auto i = 0; i <= box_count; i++)
    {
        scene->addLine(x, y, x, y + height);
        x += box_size;
    }

    this->ui->mapAreaGraphics->setScene(scene);
    this->ui->mapAreaGraphics->setRenderHint(QPainter::Antialiasing);
    this->ui->mapAreaGraphics->setRenderHint(QPainter::HighQualityAntialiasing);
}

// Slots

void astar::on_sliderZoom_valueChanged(int value)
{
    auto scale = value / 100.0;

    // GraphicsView

    this->ui->mapAreaGraphics->setTransform(QTransform::fromScale(scale, scale));
}

void astar::on_buttonBoxCount_clicked()
{
    auto text = this->ui->lineEditBoxCount->text();
    auto box_count = text.toInt();
    this->ui->mapAreaGraphics->drawGrid(box_count);
}
