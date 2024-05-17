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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DrawTable()
{
    model = new QSqlTableModel(this);
    model->setTable("Mutants");
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
};

void MainWindow::on_pushButton_clicked() // задание действия для кнопки
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Выберите SQLITE базу данных"), "", tr("Databases (*.db)")); // данная строка задает открытие диалогово окна с фильтром. Фильтр прописан чтобы показывались только файлы с расширением db
    db = new DataBaseManager(); // указываем путь к бд
    db->OpenDB(fileName);
    QMessageBox msgBox;
    if (db->IsOpen()) // проверка открытия базы
    {
        msgBox.setText("Успех! База данных открылась");
        msgBox.exec();
        this->DrawTable();
    }
    else
    {
        msgBox.setText("Ошибка. База данных не открылась. ПРоверьте правильность пути и файла.");
        msgBox.exec();
    }
}



void MainWindow::on_pushButton_2_clicked()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows(); // сохраняем выделенные строки в массив
    foreach (const QModelIndex &index, selectedRows) {
        ui->tableView->model()->removeRow(index.row()); // удаляем строки в цикле
    }
    // перерисовываем таблицу с уже новыми данными
    model = new QSqlTableModel(this);
    model->setTable("Mutants");
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}
