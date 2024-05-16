#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog> // обязательно для подключения, так как без него не будет работать выбор файла
#include <QtSql>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

class DBCONNECT
{
    private:
        QSqlDatabase m_db;
    public:
        DBCONNECT(const QString& path);
};

DBCONNECT::DBCONNECT(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE", "DATA");
    m_db.setDatabaseName(path);
    if (!m_db.open())
    {
        qDebug() << "Ошибка. База данных не открылась";
    }
    else
    {
        qDebug() << "Успех. База данных открылась";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Выберите SQLITE базу данных"), "", tr("Databases (*.db)"));
    DBCONNECT our_db(fileName);
}

