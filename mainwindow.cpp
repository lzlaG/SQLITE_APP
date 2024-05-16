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
    m_db = QSqlDatabase::addDatabase("QSQLITE");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked() // задание действия для кнопки
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Выберите SQLITE базу данных"), "", tr("Databases (*.db)")); // данная строка задает открытие диалогово окна с фильтром. Фильтр прописан чтобы показывались только файлы с расширением db
    m_db.setDatabaseName(fileName);
    QMessageBox msgBox;
    if (!m_db.open())
    {
        msgBox.setText("База данных не открылась. Проверьте корректность пути и файла");
        msgBox.exec();
    }
    else
    {
        msgBox.setText("Успех! База данных открылась");
        msgBox.exec();
        //query = new QSqlQuery(m_db);
        //query->exec("select * from Mutants;");

        model = new QSqlTableModel(this,m_db);
        model->setTable("Mutants");
        model->select();
        ui->tableView->setModel(model);
    }
}


