#include "writeobject.h"
#include "mutant.h"
#include <QStandardItemModel>

WriteObject::WriteObject(QObject *parent)
    : QObject{parent}
{

}
void WriteObject::WriteDataToTable(Iterator<ScumPointer> *it)
{
    Model->setColumnCount(4);
    int i = 0;
    for(it->First(); !it->IsDone(); it->Next())
    {
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
        i+=1;
    }
    Model->setHeaderData(0,Qt::Horizontal,"Тип мутанта");
    Model->setHeaderData(3,Qt::Horizontal,"Возраст мутанта");

}

void WriteObject::Create_Containers(int UserChoice)
{
    Iterator<ScumPointer> *OurIterator;
    int random_amount_of_mutant = 10000;
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
    Create_Containers(UserChoice);
    count++;
    qDebug() << count;
    emit finished();
}

void WriteObject::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(running);
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
