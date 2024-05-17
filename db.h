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
        QString AditionalInfo(int id)
        {
            if (!my_db.open())
            {
                qWarning() << "Не удалось подключиться к базе данных";
            }
            QSqlQuery query;
            query.prepare("SELECT visit_count,datetime(last_visit_time/1000000-11644473600,'unixepoch','localtime') FROM urls WHERE (id = "+QString::number(id)+")");
            if (!query.exec())
            {
                qWarning() << "Не удалось выполнить запрос";
            }
            query.next();
            QString name = query.value(0).toString()+" "+query.value(1).toString();
            return name;
        }
};

#endif // DB_H
