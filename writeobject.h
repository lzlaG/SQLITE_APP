#ifndef WRITEOBJECT_H
#define WRITEOBJECT_H

#include <QObject>
#include <QDebug>
#include "mutant.h"
#include <QStandardItemModel>



class WriteObject : public QObject
{
    Q_OBJECT
    bool m_running = true;
    int count;
    QStandardItemModel *Model;
    int UserChoice;
    QString Path;
    int StartRow;
    int AmountOfRow;
public:
    explicit WriteObject(QObject *parent = nullptr);
    bool running() const;
    void WriteDataToTable(Iterator<ScumPointer> *it);
    void Create_Containers();

signals:
    void finished();
    void runningChanged(bool running);
public slots:
    void run(); // Метод с полезной нагрузкой, который может выполняться в цикле
    void setModel(QStandardItemModel *model);
    void setUserChoice(int userchoice);
    void setPathToDB(QString path);
    void setStartAndAmount(int startrow, int amountofrow);
};

#endif // WRITEOBJECT_H
