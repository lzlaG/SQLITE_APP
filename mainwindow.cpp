#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    ui->FillContainer->setDisabled(true);
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
    QModelIndex HideData = model->index(SelectedIndex.row(),1); // получаем данные из нужного столбца по выделенному индексу
    QModelIndex HideVisitCount = model->index(SelectedIndex.row(),4);
    ui->add_info->setText("Дополнительная информация\nДата последнего посещения: "+HideData.data().toString()
                          +"\nКоличество посещений: "+HideVisitCount.data().toString()); // задаем лейблу наш текст
}



void MainWindow::on_ListCheckBox_clicked()
{
    ui->VectorCheckBox->setChecked(false);
    ui->DbCheckBox->setChecked(false);
    if(ui->ListCheckBox->checkState())
    {
        ui->FillContainer->setEnabled(true);
        Container_User_Choice = 1;
    }
    else
    {
        ui->FillContainer->setEnabled(false);
    }
}

void MainWindow::on_VectorCheckBox_clicked()
{
    ui->ListCheckBox->setChecked(false);
    ui->DbCheckBox->setChecked(false);
    if(ui->VectorCheckBox->checkState())
    {
        ui->FillContainer->setEnabled(true);
        Container_User_Choice = 2;
    }
    else
    {
        ui->FillContainer->setEnabled(false);
    }
}


void MainWindow::on_DbCheckBox_clicked()
{
    ui->ListCheckBox->setChecked(false);
    ui->VectorCheckBox->setChecked(false);
    if(ui->DbCheckBox->checkState())
    {
        ui->FillContainer->setEnabled(true);
        Container_User_Choice = 3;
    }
    else
    {
        ui->FillContainer->setEnabled(false);
    }
}
void ItogTask(Iterator<ScumPointer> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        const ScumPointer currentMutant = it->GetCurrent();
        QString ss;
        qDebug() << "----------------------------------" << "\n";
        qDebug() << ss.fromStdString(PrintMutantType(currentMutant->GetType())) << "\n";
        qDebug() << ss.fromStdString(PrintHandPower(currentMutant->GetHandPower())) << "\n";
        qDebug() << ss.fromStdString(PrintLegPower(currentMutant->GetLegPower())) << "\n";
        qDebug() << ss.fromStdString(PrintAgeOfMutant(currentMutant->GetAgeOfMutant())) << "\n";
    }
}
void MainWindow::Create_Containers(int User_Choice)
{
    Iterator<ScumPointer> *OurIterator;
    int random_amount_of_mutant = rand()%(100-10+1)+1;
    cout << "Генерируем " << random_amount_of_mutant << " мутантов" << "\n";
    if (User_Choice == 1)
    {
        MutantContainer scumcell_list(random_amount_of_mutant);
        for(int i=0; i<random_amount_of_mutant; i++)
        {
            scumcell_list.AddMutant(MutantFactory(MutantType(rand()%3)));
        };

        OurIterator = scumcell_list.GetIterator();
        ItogTask(OurIterator);
    };
    if(User_Choice == 2)
    {
        WildMutantContainer scumcell_vector;
        for(int i=0; i<random_amount_of_mutant; i++)
        {
            scumcell_vector.AddMutant(MutantFactory(MutantType(rand()%3)));
        };
        OurIterator = scumcell_vector.GetIterator();
        ItogTask(OurIterator);
    };
    /*
    if(User_Choice == 3)
    {
        UltraWildMutantContainer scumcell_sqlite(path_to_db);
        scumcell_sqlite.ClearDB();
        for(int i=0; i<random_amount_of_mutant; i++)
        {
            scumcell_sqlite.AddMutant(MutantFactory(MutantType(rand()%3)));
        };
        OurIterator = scumcell_sqlite.GetIterator();
        ItogTask(OurIterator);
    };*/
}

void MainWindow::on_FillContainer_clicked()
{
    Create_Containers(Container_User_Choice);
}

