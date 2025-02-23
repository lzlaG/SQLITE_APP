#include "writeobject.h"
#include "mutant.h"
#include <QStandardItemModel>
#include <QElapsedTimer>
#include <QDebug>
#include <QThread>
#include <ctime>
#include <iomanip>
#include <sstream>

WriteObject::WriteObject(QObject *parent)
    : QObject{parent}
{

}
// функция для форматирования времени
QString timeElapsedToString(qint64 elapsed)
{
    int milliseconds = elapsed % 1000;
    elapsed /= 1000;
    int seconds = elapsed % 60;
    elapsed /= 60;
    int minutes = elapsed % 60;
    elapsed /= 60;
    int hours = elapsed;
    return QString("%1:%2:%3.%4")
            .arg(hours, 2, 10, QChar('0'))
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'))
            .arg(milliseconds, 3, 10, QChar('0'));
}

string generateRandomString(size_t length) {
    const char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";
    const size_t max_index = sizeof(charset) - 1;

    std::string random_string;
    for (size_t i = 0; i < length; ++i) {
        random_string += charset[rand() % max_index];
    }
    return random_string;
}
//функция записи данных
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
        i+=1;
    }
}

// функция чтения данных
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
        string path_to_db = "mutant"+generateRandomString(10)+".db";
        UltraWildMutantContainer scumcell_sqlite(path_to_db);
        scumcell_sqlite.ClearDB();
        for(int i=0; i<random_amount_of_mutant; i++)
        {
            scumcell_sqlite.AddMutant(MutantFactory(MutantType(rand()%3)));
        };
        OurIterator = scumcell_sqlite.GetIterator();
        WriteDataToTable(OurIterator);
    };
}

//функция где выполняется все необходимое
void WriteObject::run()
{
    QElapsedTimer timer;
    timer.start();
    Create_Containers();
    TimeSpended = "Времени потрачено на операцию: \n"+timeElapsedToString(timer.elapsed());
    emit UpdateLabel(TimeSpended); // издаем сигнал об обновлении текстового лейбла
    emit finished(); // издаем сигнал о завершении работы
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
