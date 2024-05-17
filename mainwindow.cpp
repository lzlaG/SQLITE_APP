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
    ui->pushButton_2->setDisabled(true);
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
    ui->tableView->setModel(model); // задаем модель
    ui->tableView->resizeColumnsToContents(); // делаем колонки размером с сосдержимым
    //разрешаем выделение строк
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
};

void MainWindow::on_pushButton_clicked() // задание действия для кнопки открытия бд
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Выберите SQLITE базу данных"), "", tr("Databases (*.db)")); // данная строка задает открытие диалогово окна с фильтром. Фильтр прописан чтобы показывались только файлы с расширением db
    db = new DataBaseManager(); // указываем путь к бд
    db->OpenDB(fileName); // открываем бд
    QMessageBox msgBox; // создаем сообщение
    if (db->IsOpen()) // проверка открытия базы
    {
        msgBox.setText("Успех! База данных открылась"); // задаем текст сообщения
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
    selectedRows = ui->tableView->selectionModel()->selectedRows(); // сохраняем выделенные строки в массив
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
}

