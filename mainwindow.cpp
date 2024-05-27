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
    //connect(&Thread_1, &QThread::started, &Object_1, &WriteObject::run);
    //connect(&Object_1, &WriteObject::finished, &Thread_1, &QThread::terminate);
    //Object_1.moveToThread(&Thread_1);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FillTree()
{
    model = new QStandardItemModel(this); // инициализируем новую модель
    model->setColumnCount(5);
};


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QModelIndex SelectedIndex = ui->treeView->selectionModel()->currentIndex(); // берем выделенный индекс
    QModelIndex HideHandPower = model->index(SelectedIndex.row(),1); // получаем данные из нужного столбца по выделенному индексу
    QModelIndex HideLegPower = model->index(SelectedIndex.row(),2);
    ui->add_info->setText("Дополнительная информация\nСила ног: "+HideLegPower.data().toString()
                          +"\nСила рук: "+HideHandPower.data().toString()); // задаем лейблу наш текст
}



void MainWindow::on_ListCheckBox_clicked()
{
    ui->VectorCheckBox->setChecked(false);
    ui->DbCheckBox->setChecked(false);
    if(ui->ListCheckBox->checkState())
    {
        //ui->FillContainer->setEnabled(true);
        Container_User_Choice = 1;
    }
    else
    {
        //ui->FillContainer->setEnabled(false);
    }
}

void MainWindow::on_VectorCheckBox_clicked()
{
    ui->ListCheckBox->setChecked(false);
    ui->DbCheckBox->setChecked(false);
    if(ui->VectorCheckBox->checkState())
    {
        //ui->FillContainer->setEnabled(true);
        Container_User_Choice = 2;
    }
    else
    {
        //ui->FillContainer->setEnabled(false);
    }
}


void MainWindow::on_DbCheckBox_clicked()
{
    ui->ListCheckBox->setChecked(false);
    ui->VectorCheckBox->setChecked(false);
    if(ui->DbCheckBox->checkState())
    {
        //ui->FillContainer->setEnabled(true);
        Container_User_Choice = 3;
    }
    else
    {
        //ui->FillContainer->setEnabled(false);
    }
}


void MainWindow::on_No_Thread_Button_clicked()
{
    model = new QStandardItemModel(this);
    Object_1.setModel(model);
    Object_1.setUserChoice(Container_User_Choice);
    Object_1.run();
    ui->treeView->setModel(model);
}

