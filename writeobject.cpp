#include "writeobject.h"
#include "mutant.h"
#include <QStandardItemModel>
#include <QElapsedTimer>
#include <QDebug>
#include <QThread>
WriteObject::WriteObject(QObject *parent)
    : QObject{parent}
{

}
void WriteObject::WriteDataToTable(Iterator<ScumPointer> *it)
{
    int i = StartRow;
    for(it->First(); !it->IsDone(); it->Next())
    {
        QThread::msleep(30); //время которое тратим на обработку одного объекта
        const ScumPointer currentMutant = it->GetCurrent();
        QString MS;
        QStandardItem *typeofmutant = new QStandardItem(
                    MS.fromStdString(PrintMutantType(currentMutant->GetType())));
        QStandardItem *handpower = new QStandardItem(
                    MS.fromStdString(PrintHandPower(currentMutant->GetHandPower())));
        QStandardItem *legpower = new QStandardItem(
                    MS.fromStdString(PrintLegPower(currentMutant->GetLegPower())));
        QStandardItem *agemutant = new QStandardItem(
                    MS.fromStdString(PrintAgeOfMutant(currentMutant->GetAgeOfMutant())));
        Model->setItem(i, 0, typeofmutant);
        Model->setItem(i, 1, handpower);
        Model->setItem(i, 2, legpower);
        Model->setItem(i, 3, agemutant);
        emit UpdateProgressBar(i);
        qDebug() << i;
        i+=1;
    }
}

void WriteObject::Create_Containers()
{
    Iterator<ScumPointer> *OurIterator;
    int random_amount_of_mutant = AmountOfRow;
    if (UserChoice == 1)
    {
        MutantContainer scumcell_list(random_amount_of_mutant);
        for(int i=0; i<random_amount_of_mutant; i++)
        {
            scumcell_list.AddMutant(MutantFactory(MutantType(rand()%3)));
        };

        OurIterator = scumcell_list.GetIterator();
        WriteDataToTable(OurIterator);
    };
    if(UserChoice == 2)
    {
        WildMutantContainer scumcell_vector;
        for(int i=0; i<random_amount_of_mutant; i++)
        {
            scumcell_vector.AddMutant(MutantFactory(MutantType(rand()%3)));
        };
        OurIterator = scumcell_vector.GetIterator();
        WriteDataToTable(OurIterator);
    };
    if(UserChoice == 3)
    {
        UltraWildMutantContainer scumcell_sqlite(Path.toStdString());
        scumcell_sqlite.ClearDB();
        for(int i=0; i<random_amount_of_mutant; i++)
        {
            scumcell_sqlite.AddMutant(MutantFactory(MutantType(rand()%3)));
        };
        OurIterator = scumcell_sqlite.GetIterator();
        WriteDataToTable(OurIterator);
    };
}

bool WriteObject::running() const
{
    return m_running;
}

void WriteObject::run()
{
    count = 0;
    // Переменная m_running отвечает за работу объекта в потоке.
    // При значении false работа завершается
    QElapsedTimer timer;
    timer.start();
    Create_Containers();
    count++;
    qDebug() << timer.elapsed();
    m_running = false;
    emit finished();
}

void WriteObject::setModel(QStandardItemModel *model)
{
    Model = model;
}

void WriteObject::setUserChoice(int userchoice)
{
    UserChoice = userchoice;
}

void WriteObject::setPathToDB(QString path)
{
    Path = path;
};

void WriteObject::setStartAndAmount(int startrow, int amountofrow)
{
    StartRow = startrow;
    AmountOfRow = amountofrow;
}
