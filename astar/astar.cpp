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
    this->ui->mapAreaGraphics->drawGrid(30);
    this->ui->lineEditBoxCount->setText("30");
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

void astar::on_buttonCalculate_clicked()
{
    auto last_box = this->ui->mapAreaGraphics->drawing_params.box_count - 1;
    auto maze = this->ui->mapAreaGraphics->get_maze();
    astar_algorithm alg(maze, QPoint(0, 0), QPoint(last_box, last_box));
    auto result = alg.calculate(this->ui->mapAreaGraphics);
    this->ui->mapAreaGraphics->drawResult(result);
}
void astar::on_buttonResetUI_clicked()
{
    this->ui->mapAreaGraphics->setUpGui();
    this->setUpGui();
}
