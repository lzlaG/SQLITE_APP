#ifndef WRITEOBJECT_H
#define WRITEOBJECT_H

#include <QObject>
#include <QDebug>
#include "mutant.h"
#include <QStandardItemModel>



class WriteObject : public QObject // класс обертка для управления потоком
{
    Q_OBJECT
    QStandardItemModel *Model; // указатель для работы с моделью
    int UserChoice; // выбор пользователя
    QString Path; // путь до бд
    int StartRow; // стартовая строка
    int AmountOfRow; // количество записей
    QString TimeSpended; // потраченное время на выполненение
public:
    explicit WriteObject(QObject *parent = nullptr);
    void WriteDataToTable(Iterator<ScumPointer> *it); // запись данных
    void Create_Containers(); // чтение данных

signals:
    void finished(); // сигнал для оповощении о том, что работа закончена
    void runningChanged(bool running);
    void UpdateProgressBar(int Value); // сигнал для обновления progress bar
    void UpdateLabel(QString value); // сигнал для обновления текста лейбла
public slots:
    void run(); // Метод с полезной нагрузкой, который может выполняться в цикле
    void setModel(QStandardItemModel *model); // метод для задания модели, где будут храниться данные
    void setUserChoice(int userchoice); // метод для сохранения  выбора пользователя
    void setPathToDB(QString path); // метод для получения пути до бд
    void setStartAndAmount(int startrow, int amountofrow); // метод для настройки старта и конца
};

#endif // WRITEOBJECT_H
