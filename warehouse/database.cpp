#include "database.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

database::database()
{
    //Подключение к базе данных SQL
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
    }
}
