#ifndef WRITEOBJECT_H
#define WRITEOBJECT_H

#include <QObject>
#include <QDebug>
#include "mutant.h"
#include <QStandardItemModel>



class WriteObject : public QObject
{
    Q_OBJECT
    bool m_running;
    int count;
    QStandardItemModel *Model;
    int UserChoice;
    QString Path;
public:
    explicit WriteObject(QObject *parent = nullptr);
    bool running() const;
    void WriteDataToTable(Iterator<ScumPointer> *it);
    void Create_Containers(int User_Choice);

signals:
    void finished();
    void runningChanged(bool running);
public slots:
    void run(); // Метод с полезной нагрузкой, который может выполняться в цикле
    void setRunning(bool running);
    void setModel(QStandardItemModel *model);
    void setUserChoice(int userchoice);
    void setPathToDB(QString path);
};

#endif // WRITEOBJECT_H
