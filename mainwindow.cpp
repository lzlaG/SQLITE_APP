#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog> // обязательно для подключения, так как без него не будет работать выбор файла
#include <QtSql>
#include <QtGui>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_db = QSqlDatabase::addDatabase("QSQLITE"); // задаем драйвер для бд
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked() // задание действия для кнопки
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Выберите SQLITE базу данных"), "", tr("Databases (*.db)")); // данная строка задает открытие диалогово окна с фильтром. Фильтр прописан чтобы показывались только файлы с расширением db
    m_db.setDatabaseName(fileName); // указываем путь к бд
    QMessageBox msgBox;
    if (!m_db.open()) // проверка открытия базы
    {
        msgBox.setText("База данных не открылась. Проверьте корректность пути и файла");
        msgBox.exec();
    }
    else
    {
        msgBox.setText("Успех! База данных открылась");
        msgBox.exec();
        model = new QSqlTableModel(this,m_db); // инициализируем модель
        model->setTable("Mutants"); // задаем таблицу для моедли
        model->select(); // выбираем все из модели
        ui->tableView->setModel(model); // передаем модель в tableView
        ui->tableView->resizeColumnsToContents(); // делаем чтобы колонки совпадали по размеру с содержимым
    }
}



void MainWindow::on_pushButton_2_clicked()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows(); // сохраняем выделенные строки в массив
    foreach (const QModelIndex &index, selectedRows) {
        ui->tableView->model()->removeRow(index.row()); // удаляем строки в цикле
    }
    // перерисовываем таблицу с уже новыми данными
    model = new QSqlTableModel(this,m_db);
    model->setTable("Mutants");
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}


// trash
/*
void MainWindow::on_tableView_clicked(const QModelIndex &index){};
void MainWindow::on_pushButton_3_clicked(){};
*/
