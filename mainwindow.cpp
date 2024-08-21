#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "writeobject.h"
#include <QFileDialog> // обязательно для подключения, так как без него не будет работать выбор файла
#include <QtSql> // qt sql библиотека
#include <QtGui>
#include <QMessageBox>
#include <QtWidgets>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //делаем кнопку неактивной по умолчанию
    ui->progressBar->setValue(0); // устанавлваем значение по умолчанию для прогресс бара 0
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QModelIndex SelectedIndex = ui->treeView->selectionModel()->currentIndex(); // берем выделенный индекс
    QModelIndex HideHandPower = model->index(SelectedIndex.row(),1); // получаем данные из нужного столбца по выделенному индексу
    QModelIndex HideLegPower = model->index(SelectedIndex.row(),2);
    ui->add_info->setText("Дополнительная информация\nСила ног: "+HideLegPower.data().toString()
                          +"\nСила рук: "+HideHandPower.data().toString()); // задаем лейблу наш текст
}


//чекоксы для выбора контейнера
void MainWindow::on_ListCheckBox_clicked()
{
    ui->VectorCheckBox->setChecked(false);
    ui->DbCheckBox->setChecked(false);
    if(ui->ListCheckBox->checkState())
    {
        ui->No_Thread_Button->setEnabled(true);
        ui->One_Thread_Button->setEnabled(true);
        ui->Two_Thread_Button->setEnabled(true);
        Container_User_Choice = 1;
    }
    else
    {
        ui->No_Thread_Button->setEnabled(false);
        ui->One_Thread_Button->setEnabled(false);
        ui->Two_Thread_Button->setEnabled(false);
    }
}

void MainWindow::on_VectorCheckBox_clicked()
{
    ui->ListCheckBox->setChecked(false);
    ui->DbCheckBox->setChecked(false);
    if(ui->VectorCheckBox->checkState())
    {
        ui->No_Thread_Button->setEnabled(true);
        ui->One_Thread_Button->setEnabled(true);
        ui->Two_Thread_Button->setEnabled(true);
        Container_User_Choice = 2;
    }
    else
    {
        ui->No_Thread_Button->setEnabled(false);
        ui->One_Thread_Button->setEnabled(false);
        ui->Two_Thread_Button->setEnabled(false);
    }
}


void MainWindow::on_DbCheckBox_clicked()
{
    ui->ListCheckBox->setChecked(false);
    ui->VectorCheckBox->setChecked(false);
    if(ui->DbCheckBox->checkState())
    {
        ui->No_Thread_Button->setEnabled(true);
        ui->One_Thread_Button->setEnabled(true);
        ui->Two_Thread_Button->setEnabled(true);
        Container_User_Choice = 3;
    }
    else
    {
        ui->No_Thread_Button->setEnabled(false);
        ui->One_Thread_Button->setEnabled(false);
        ui->Two_Thread_Button->setEnabled(false);
    }
}

//кнопка для обработки данных без потоков
void MainWindow::on_No_Thread_Button_clicked()
{
    model = new QStandardItemModel(this);
    Object_1 = new WriteObject(); // создааем часть данных
    /*
    if (Container_User_Choice == 3)
    {
        QString FileName = QFileDialog::getOpenFileName(this,
                    tr("Выберите SQLITE базу данных"), "", tr("SQLITE3 Databases (*.db)"));
        Object_1->setPathToDB(FileName);
    }
    */
    connect(Object_1, SIGNAL(UpdateProgressBar(int)), ui->progressBar, SLOT(setValue(int)));
    connect(Object_1, SIGNAL(UpdateLabel(QString)), ui->time_label, SLOT(setText(QString)));

    model->setColumnCount(4);

    model->setHeaderData(0,Qt::Horizontal,"Тип мутанта");
    model->setHeaderData(3,Qt::Horizontal,"Возраст мутанта");

    Object_1->setModel(model); // задаем модель, где будем хранить данные
    Object_1->setUserChoice(Container_User_Choice); // учитываем мнение пользователя при выборе контейнера
    Object_1->setStartAndAmount(0, 2000); // устанавливаем количество записей
    Object_1->run(); // запускаем обработку

    ui->treeView->setModel(model);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
}


void MainWindow::on_One_Thread_Button_clicked()
{
    model = new QStandardItemModel(this);
    Object_1 = new WriteObject();
    Thread_1 = new QThread(); // создаем поток
    ui->progressBar->setRange(0,1999);
    /*
    if (Container_User_Choice == 3)
    {
        QString FileName = QFileDialog::getOpenFileName(this,
                    tr("Выберите SQLITE базу данных"), "", tr("SQLITE3 Databases (*.db)"));
        Object_1->setPathToDB(FileName);
    }
    */
    model->setColumnCount(4);

    model->setHeaderData(0,Qt::Horizontal,"Тип мутанта");
    model->setHeaderData(3,Qt::Horizontal,"Возраст мутанта");

    connect(Thread_1, &QThread::started, Object_1, &WriteObject::run); // соединяем функцию объекта для выполнения в потоке
    connect(Object_1, &WriteObject::finished, Thread_1, &QThread::terminate); // соединяем сигнал от объекта таким образом, чтобы при завершении поток уничтожался
    connect(Object_1, SIGNAL(UpdateProgressBar(int)), ui->progressBar, SLOT(setValue(int)));
    connect(Object_1, SIGNAL(UpdateLabel(QString)), ui->time_label, SLOT(setText(QString)));
    Object_1->moveToThread(Thread_1); // перемещаем объект в поток

    Object_1->setModel(model);
    Object_1->setUserChoice(Container_User_Choice);
    Object_1->setStartAndAmount(0, 2000);


    Thread_1->start(); // запускаем поток

    ui->treeView->setModel(model);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
}


void MainWindow::on_Two_Thread_Button_clicked()
{
    model = new QStandardItemModel(this);
    //по аналогии с первым создаем два потока и два объекта для них
    Object_1 = new WriteObject();
    Object_2 = new WriteObject();
    Thread_1 = new QThread();
    Thread_2 = new QThread();
    ui->progressBar->setRange(0,999);
    /*
    if (Container_User_Choice == 3)
    {
        QString FileName = QFileDialog::getOpenFileName(this,
                    tr("Выберите SQLITE базу данных"), "", tr("SQLITE3 Databases (*.db)"));
        Object_1->setPathToDB(FileName);
        Object_2->setPathToDB(FileName);
    }
    */
    model->setColumnCount(4);

    model->setHeaderData(0,Qt::Horizontal,"Тип мутанта");
    model->setHeaderData(3,Qt::Horizontal,"Возраст мутанта");

    connect(Thread_1, &QThread::started, Object_1, &WriteObject::run);
    connect(Object_1, &WriteObject::finished, Thread_1, &QThread::terminate);

    connect(Thread_2, &QThread::started, Object_2, &WriteObject::run);
    connect(Object_2, &WriteObject::finished,Thread_2, &QThread::terminate);

    connect(Object_1, SIGNAL(UpdateProgressBar(int)), ui->progressBar, SLOT(setValue(int)));
    connect(Object_1, SIGNAL(UpdateLabel(QString)), ui->time_label, SLOT(setText(QString)));

    Object_1->moveToThread(Thread_1);
    Object_2->moveToThread(Thread_2);
    Object_1->setModel(model);
    Object_1->setUserChoice(Container_User_Choice);
    Object_1->setStartAndAmount(0, 1000);
    Object_2->setModel(model);
    Object_2->setUserChoice(Container_User_Choice);
    Object_2->setStartAndAmount(1000, 1000);
    Thread_1->start();
    Thread_2->start();

    ui->treeView->setModel(model);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
}

