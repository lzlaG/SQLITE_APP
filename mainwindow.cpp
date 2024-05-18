#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog> // обязательно для подключения, так как без него не будет работать выбор файла
#include <QtSql> // qt sql библиотека
#include <QtGui>
#include <QMessageBox>
struct NodeData
{
    int id;
    QString url;
    QString date;
    QString
};

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
            tr("Выберите SQLITE базу данных"), "", tr("Chromium Databases (History*)")); // данная строка задает открытие диалогово окна с фильтром. Фильтр прописан чтобы показывались только файлы с расширением db
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

void MainWindow::FillTree()
{
    QSqlQuery query("SELECT datetime(last_visit_time / 1000000 - 11644473600, 'unixepoch', 'localtime'),url,title,visit_count FROM urls;");

    model = new QStandardItemModel(this);
    rootItem = model->invisibleRootItem();
    model->setColumnCount(2);
    for (int i=0; i<1000000; i++)
    {
        QStandardItem *item1 = new QStandardItem(QString("Столбец 1, строка %1").arg(i));
        QStandardItem *item2 = new QStandardItem(QString("Столбец 2, строка %1").arg(i));
        model->setItem(i, 0, 1);
        model->setItem(i, 1, item2);
    };
};
void MainWindow::on_debug_button_clicked()
{
    FillTree();
    ui->treeView->setModel(model);
    ui->treeView->show();
};

