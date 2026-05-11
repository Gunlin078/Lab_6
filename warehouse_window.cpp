#include "warehouse_window.h"
#include "./ui_warehouse_window.h"

WarehouseWindow::WarehouseWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WarehouseWindow)
{
    ui->setupUi(this);
    //getProductsVectorFromJSON("C:/Qt/Lab_6/include/additionalResources/warehouse.json");

    if(ui->Output_TableW){
        ui->Output_TableW->setColumnCount(4);
        QStringList headers = {"ID", "Name (Mod)", "Price", "Expiration Date"};
        ui->Output_TableW->setHorizontalHeaderLabels(headers);

        ui->Output_TableW->setColumnWidth(0, 30);
        ui->Output_TableW->setColumnWidth(1, 180);
        ui->Output_TableW->verticalHeader()->setVisible(false);

        ui->Output_TableW->horizontalHeader()->setStretchLastSection(true);
        ui->Output_TableW->setAlternatingRowColors(true);
        ui->Output_TableW->setEditTriggers(QAbstractItemView::NoEditTriggers);}
    QObject::connect(ui->Enter_PB, &QPushButton::clicked, [this](){processor.output(ui->GettingPath_LE->text(), ui->Output_TE); });

    QObject::connect(ui->Enter_PB, &QPushButton::clicked, [this](){processor.outputtingJsonToATable(
                                                                         ui->GettingPath_LE->text(), ui->Output_TableW); });
}

WarehouseWindow::~WarehouseWindow()
{
    delete ui;
}
/*
void outputtingJsonToATable(const json& data, QTableWidget* table){
    table->setRowCount(0);
    int row = 0;
    for (const auto& item : data){
        table->insertRow(row);

        int id = item["id"];
        QTableWidgetItem *itemId = new QTableWidgetItem(QString::number(id));
        itemId->setTextAlignment(Qt::AlignCenter);
        table->setItem(row, 0, itemId);

        QString originalName = QString::fromStdString(item["name"]);
        QString modifiedName = originalName;
        QTableWidgetItem *itemName = new QTableWidgetItem(modifiedName);
        table->setItem(row, 1, itemName);

        float price = item["price"];
        QTableWidgetItem *itemPrice = new QTableWidgetItem(QString::number(price, 'f', 2));
        itemPrice->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        table->setItem(row, 2, itemPrice);

        QString expiritionDate = QString::fromStdString(item["expirition_date"]);
        QTableWidgetItem *itemDate = new QTableWidgetItem(expiritionDate);
        itemDate->setTextAlignment(Qt::AlignCenter);
        table->setItem(row, 3, itemDate);

        row++;
    }
}
*/
