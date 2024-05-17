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
        void DeleteRow(int row_index) // функция для удаления записи из бд
        {
            QSqlQuery query;
            query.prepare("delete from urls where (id = "+QString::number(row_index)+")");
            query.exec();
        };
};

#endif // DB_H
