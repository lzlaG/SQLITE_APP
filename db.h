#ifndef DB_H
#define DB_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlTableModel>


class DataBaseManager //класс для управления бд
{
    private:
        QSqlDatabase my_db; // наша база данных, с которой будем работать
    public:
        DataBaseManager(){my_db = QSqlDatabase::addDatabase("QSQLITE");}; // создаем соединение с драйвером QSQLITE при создании класса
        void OpenDB(QString path){my_db.setDatabaseName(path);}; //открываем бд по указонному пути
        bool IsOpen() // функция для проверки открыта база данных или нет
        {
            if (!my_db.open())
            {
                return false;
            }
            else
            {
                return true;
            }
        };
};

#endif // DB_H
