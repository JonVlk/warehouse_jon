#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Подключение к бд SQL
    QSqlDatabase db = QSqlDatabase::database("warehousejonvlk");

    if (!db.isValid()) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
        db.setDatabaseName("DRIVER={SQL Server};"
                            "Server=192.168.50.184;"
                            "Database=warehousejonvlk;"
                            "Uid=userSQL;"
                            //"Port=1433;"
                            "Pwd=userSQL1;"
                            "WSID=.\"");



    if (!db.open()) {
        qCritical() << db.lastError();
    }





    QSqlQuery query;
    query.exec("SELECT id, part_name, quantity, unit, price, average_price FROM warehouse_table");

    while (query.next()) {
        QString id = query.value(0).toString();
        QString part_name = query.value(1).toString();
        QString quantity = query.value(2).toString();
        QString unit = query.value(3).toString();
        QString price = query.value(4).toString();
        QString average_price = query.value(5).toString();


        ui->textEdit->insertPlainText(id+" "+part_name+" "+quantity+" "+unit+" "+price+" "
                                      +average_price+"\n");
                            }

        }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

}
