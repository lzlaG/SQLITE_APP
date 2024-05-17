#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog> // обязательно для подключения, так как без него не будет работать выбор файла
#include <QtSql> // qt sql библиотека
#include <QtGui>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_2->setDisabled(true); // делаем кнопку удаления по умолчанию выключенной
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DrawTable()
{
    model = new QSqlTableModel(this);
    model->setTable("urls");
    model->select();
    ui->tableView->setModel(model); // задаем модель
    ui->tableView->resizeColumnsToContents(); // делаем колонки размером с сосдержимым
    // скрываем лишние столбцы
    ui->tableView->hideColumn(3);
    ui->tableView->hideColumn(4);
    ui->tableView->hideColumn(5);
    ui->tableView->hideColumn(6);
    //разрешаем выделение строк
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
};

void MainWindow::on_pushButton_clicked() // задание действия для кнопки открытия бд
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Выберите SQLITE базу данных"), "", tr("Chromium Databases (History)")); // данная строка задает открытие диалогово окна с фильтром. Фильтр прописан чтобы показывались только файлы с расширением db
    db = new DataBaseManager(); // указываем путь к бд
    db->OpenDB(fileName); // открываем бд
    QMessageBox msgBox; // создаем сообщение
    if (db->IsOpen()) // проверка открытия базы
    {
        msgBox.setText("Успех! База данных открылась"); // задаем текст сообщения
        msgBox.exec();
        this->DrawTable(); // отрисовываем таблицу в случае успешного открытия
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
    this->DrawTable();// перерисовываем таблицу с уже новыми данными
    QModelIndex current = ui->tableView->currentIndex();
    int id = current.sibling(current.row(), 0).data().toInt();
    db->DeleteRow(id);
    ui->pushButton_2->setDisabled(true); // делаем кнопку снова не активной после удаления записи
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    ui->pushButton_2->setEnabled(true); // делаем кнопку удаления активной, если выделена строка
    QModelIndex current = ui->tableView->currentIndex();
    int id = current.sibling(current.row(), 0).data().toInt();
    QString additional_information = db->AditionalInfo(id);
    ui->label->setText(additional_information);
}

