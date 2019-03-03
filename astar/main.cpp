#include <QApplication>
#include "astar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    astar w;
    w.show();

    return a.exec();
}
