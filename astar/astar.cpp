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

// Slots

void astar::on_sliderZoom_valueChanged(int value)
{
    auto scale = value / 100.0;

    // GraphicsView
    this->ui->mapAreaGraphics->drawing_params.scale = scale;
    this->ui->mapAreaGraphics->setTransform(QTransform::fromScale(scale, scale));
}

void astar::on_buttonBoxCount_clicked()
{
    auto text = this->ui->lineEditBoxCount->text();
    auto box_count = text.toInt();
    this->ui->mapAreaGraphics->drawGrid(box_count);
}
