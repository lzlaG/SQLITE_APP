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
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked() // задание действия для кнопки открытия бд
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Выберите SQLITE базу данных"), "", tr("Chromium Databases (History)")); // данная строка задает открытие диалогово окна с фильтром. Фильтр прописан чтобы показывались только файлы с расширением db
    db = new DataBaseManager(); // указываем путь к бд
    db->OpenDB(fileName); // открываем бд
    QMessageBox msgBox; // создаем сообщение
    if (db->IsOpen() && !fileName.isEmpty()) // проверка открытия базы
    {
        msgBox.setText("Успех! База данных открылась"); // задаем текст сообщения
        msgBox.exec();
    }
    else
    {
        msgBox.setText("Ошибка. База данных не открылась. ПРоверьте правильность пути и файла.");
        msgBox.exec();
    }
}

