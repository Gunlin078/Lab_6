#include "warehouse_window.h"
#include "./ui_warehouse_window.h"

WarehouseWindow::WarehouseWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WarehouseWindow)
{
    ui->setupUi(this);
    //getProductsVectorFromJSON("C:/Qt/Lab_6/include/additionalResources/warehouse.json");
    QObject::connect(ui->Enter_PB, &QPushButton::clicked, [this](){outputer.output(ui->GettingPath_LE->text(), ui->Output_TE); });
}

WarehouseWindow::~WarehouseWindow()
{
    delete ui;
}
