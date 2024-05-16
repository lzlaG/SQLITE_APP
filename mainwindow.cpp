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

class DBCONNECT // класс для управления базой данных
{
    private:
        QSqlDatabase m_db;
    public:
        DBCONNECT(const QString& path);
};

DBCONNECT::DBCONNECT(const QString &path) //конструктор для открытия базы данных и проверки(открыдась или нет)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE", "DATA");
    m_db.setDatabaseName(path);
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
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked() // задание действия для кнопки
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Выберите SQLITE базу данных"), "", tr("Databases (*.db)")); // данная строка задает открытие диалогово окна с фильтром. Фильтр прописан чтобы показывались только файлы с расширением db
    DBCONNECT our_db(fileName);
}


