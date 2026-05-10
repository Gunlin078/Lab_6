#include "warehouse_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WarehouseWindow w;
    w.show();
    return a.exec();
}
