#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlTableModel>
#include "db.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

// созданные слоты
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
protected:
    QSqlTableModel *model; // переменная для здания модели данных
    DataBaseManager *db; // бд
    void DrawTable(); // функция для отрисовки таблицы
};
#endif // MAINWINDOW_H
