#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog> // обязательно для подключения, так как без него не будет работать выбор файла
#include <QtSql> // qt sql библиотека
#include <QtGui>
#include <QMessageBox>

// структура для чтения данных
struct NodeData
{
    QString id;
    QString date;
    QString url;
    QString title;
    QString visit_count;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //делаем кнопку неактивной по умолчанию
    ui->delete_button->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FillTree()
{
    QSqlQuery query("SELECT id,datetime(last_visit_time / 1000000 - 11644473600, 'unixepoch', 'localtime'),url,title,visit_count FROM urls;");
    if (!query.exec()) {
        qWarning() << "Не удалось выполнить запрос"; // проверяем правильность запроса
        return;
    };
    model = new QStandardItemModel(this); // инициализируем новую модель
    model->setColumnCount(5); // устанавливаем количество колонок
    int i = 0; // указатель строк
    while(query.next())
    {
        // читаем данные в структуру из sql запроса
        NodeData OurData;
        OurData.id = query.value(0).toString();
        OurData.date = query.value(1).toString();
        OurData.url = query.value(2).toString();
        OurData.title = query.value(3).toString();
        OurData.visit_count = query.value(4).toString();

        // здаем данные для узла
        QStandardItem *qid = new QStandardItem(OurData.id);
        QStandardItem *qday = new QStandardItem(OurData.date);
        QStandardItem *qurl = new QStandardItem(OurData.url);
        QStandardItem *qtitle = new QStandardItem(OurData.title);
        QStandardItem *qvisit_count = new QStandardItem(OurData.visit_count);

        //привязываем данные для корневого узла
        // при каждой новой итерации цикла создается новый корневой узел
        model->setItem(i, 0,qid);
        model->setItem(i, 1, qday);
        model->setItem(i, 2, qurl);
        model->setItem(i, 3, qtitle);
        model->setItem(i, 4, qvisit_count);
        i+=1; //смещаем указатель строки
    }
    // устанавливаем заголовки нужных столбцов
    model->setHeaderData(2,Qt::Horizontal,"URL");
    model->setHeaderData(3,Qt::Horizontal,"Title");

    //расскоментировать блок ниже если интересен тест с большим количеством записей
    /*
    for (int i=0; i<1000000; i++)
    {
        QStandardItem *item1 = new QStandardItem(QString("Столбец 1, строка %1").arg(i));
        QStandardItem *item2 = new QStandardItem(QString("Столбец 2, строка %1").arg(i));
        model->setItem(i, 0, item1);
        model->setItem(i, 1, item2);
    };*/
};

void MainWindow::on_pushButton_clicked() // задание действия для кнопки открытия бд
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Выберите SQLITE базу данных"), "", tr("Chromium Databases (History*)")); // данная строка задает открытие диалогово окна с фильтром. Фильтр прописан чтобы показывались только файлы с расширением db
    db = new DataBaseManager(); // указываем путь к бд
    db->OpenDB(fileName); // открываем бд
    QMessageBox msgBox; // создаем сообщение
    if (db->IsOpen() && !fileName.isEmpty()) // проверка открытия базы
    {
        msgBox.setText("Успех! База данных открылась"); // задаем текст сообщения
        msgBox.exec();
        FillTree(); // заполняем данные
        ui->treeView->setModel(model); // задаем модель данных
        //скрываем ненужные столбцы
        ui->treeView->hideColumn(0);
        ui->treeView->hideColumn(1);
        ui->treeView->hideColumn(4);
        //отрисовываем treeview
        ui->treeView->show();
    }
    else
    {
        msgBox.setText("Ошибка. База данных не открылась. Проверьте правильность пути и файла.");
        msgBox.exec();
    }
}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QModelIndex SelectedIndex = ui->treeView->selectionModel()->currentIndex(); // берем выделенный индекс
    QModelIndex HideData = model->index(SelectedIndex.row(),1); // получаем данные из нужного столбца по выделенному индексу
    QModelIndex HideVisitCount = model->index(SelectedIndex.row(),4);
    ui->add_info->setText("Дополнительная информация\nДата последнего посещения: "+HideData.data().toString()
                          +"\nКоличество посещений: "+HideVisitCount.data().toString()); // задаем лейблу наш текст
    ui->delete_button->setDisabled(false); // активируем кнопку удаления записи
}


void MainWindow::on_delete_button_clicked()
{
    QModelIndex SelectedIndex = ui->treeView->selectionModel()->currentIndex();
    QModelIndex HideId = model->index(SelectedIndex.row(),0);
    db->DeleteRow(HideId.data().toString()); // удаляем строку из бд используя функцию из db manager
    model->removeRow(SelectedIndex.row()); // удаляем строку из узлов
    ui->treeView->update(); // обновляем представление
    ui->add_info->setText(" "); // обновляем текст лейбла, так как запись удалилась
    ui->delete_button->setDisabled(true); // возвращаем кнопку обратно в неактивное состояние
}

