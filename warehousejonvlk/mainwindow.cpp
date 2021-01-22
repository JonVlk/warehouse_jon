#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Склад, склад, склад!");
    /* Первым делом необходимо создать объект для работы с базой данных
     * и инициализировать подключение к базе данных
     * */
    db = new DataBase();
    db->connectToDataBase();

    /* Наполним базу данных записями */
    for(int i = 1; i < 5; i++){
        /* Вставляем запись в таблицу, сразу устанавливаем состояние чекбокса.
         * Если устройство имеет нечётный номер, то статус чекбокса true,
         * иначе false
         * */
        db->inserIntoDeviceTable(QVariantList() << QString::number(i & 1)
                                                << "Device " + QString::number(i)
                                                << "192.168.0." + QString::number(i)
                                                << "AA:AA:AA:AA:AA:A" + QString::number(i));
    }

    /* Настраиваем внешний вид таблицы
     * с заданием названий колонок, а также
     * Заполняем таблицу записями из базы данных
     * */
    this->createUI(QStringList() << ("id")
                                 << ("Нечетность")
                                 << ("Имя компьютера")
                                 << ("IP адрес")
                                 << ("MAC адрес")
               );
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Метод для настройки интерфейса,
 * в данном методе будет выполняться заполнение QTableWidget
 * записями из таблицы
 * */
void MainWindow::createUI(const QStringList &headers)
{
    ui->tableWidget->setColumnCount(5); // Указываем число колонок
    ui->tableWidget->setShowGrid(true); // Включаем сетку
    // Разрешаем выделение только одного элемента
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем заголовки колонок
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    // Растягиваем последнюю колонку на всё доступное пространство
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    // Скрываем колонку под номером 0
    ui->tableWidget->hideColumn(0);

    // Создаём запрос для для выборки записей из базы данных
    QSqlQuery query("SELECT "
                    DEVICE ".id, "
                    DEVICE "." DEVICE_CHECK_STATE ", "
                    DEVICE "." DEVICE_HOSTNAME ", "
                    DEVICE "." DEVICE_IP ", "
                    DEVICE "." DEVICE_MAC
                    " FROM " DEVICE);

    /* Выполняем заполнение QTableWidget записями с помощью цикла
     * */
    for(int i = 0; query.next(); i++){
        // Вставляем строку
        ui->tableWidget->insertRow(i);
        /* Устанавливаем в первую колонку id забирая его из результата SQL-запроса
         * Эта колонка будет скрыта
         * */
        ui->tableWidget->setItem(i,0, new QTableWidgetItem(query.value(0).toString()));

        // Создаём элемент, который будет выполнять роль чекбокса
        QTableWidgetItem *item = new QTableWidgetItem();
        item->data(Qt::CheckStateRole);
        /* Проверяем, на статус нечетности, если нечетное устройство, то
         * выставляем состояние чекбокса в Checked, иначе в Unchecked
         * */
        if(query.value(1).toInt() == 1){
            item->setCheckState(Qt::Checked);
        } else {
            item->setCheckState(Qt::Unchecked);
        }
        // Устанавливаем чекбокс во вторую колонку
        ui->tableWidget->setItem(i,1, item);
        // Далее забираем все данные из результата запроса и устанавливаем в остальные поля
        ui->tableWidget->setItem(i,2, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(i,3, new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(i,4, new QTableWidgetItem(query.value(4).toString()));
    }

    // Ресайзим колонки по содержимому
    ui->tableWidget->resizeColumnsToContents();
}
