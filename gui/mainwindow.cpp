#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "models/table_model.h"
#include <QtGui>
#include <QApplication>
#include <QTableView>
#include <QTreeView>
#include <QListView>
#include <QSplitter>
#include <QHeaderView>
#include <QDebug>
#include <QAbstractTableModel>
QStringList *list_s = new QStringList();
QStringList *list_gr = new QStringList();
QStringList *list_cb=new QStringList();
QStringList *list_tm = new QStringList();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "Кабинеты: " << endl;
    for (auto it = this->repoCabinets.begin(), end = this->repoCabinets.end(); it < end; ++it) {
        auto element = *it;
        qDebug() << element.toString() << endl;
    }

    qDebug() << endl << "Время: " << endl;
    for (auto it = this->repoLessonsTimes.begin(), end = this->repoLessonsTimes.end(); it < end; ++it) {
        auto element = *it;
        qDebug() << element.toString() << endl;
    }

    qDebug() << endl << "Группы: " << endl;
    for (auto it = this->repoGroupStudents.begin(), end = this->repoGroupStudents.end(); it < end; ++it) {
        auto element = *it;
        qDebug() << element.toString() << endl;
    }

    qDebug() << endl << "Дисциплины: " << endl;
    for (auto it = this->repoSubjects.begin(), end = this->repoSubjects.end(); it < end; ++it) {
        auto element = *it;
        qDebug() << element.toString() << endl;
    }

    auto s = this->repoSubjects.getById(2);
    qDebug() << "Получение по id" << endl;
    qDebug() << s.toString() << endl;

    qDebug() << "Получение по параметрам" << endl;
    for (auto e : this->repoSubjects.getByParameters(Subject("йцуйцу"))) {
        qDebug() << e.toString() << endl;
    }

    qDebug() << "Добавление элемента 'Новый элемент'" << endl;
    this->repoSubjects.add(Subject("Новый элемент"));
    qDebug() << endl << "Дисциплины: " << endl;
    for (auto e : this->repoSubjects.getAll()) {
        qDebug() << e.toString() << endl;
    }

    qDebug() << "Изменение элемента 'Новый элемент' на 'Измененный элемент'" << endl;
    this->repoSubjects.update(4, Subject("Измененный элемент"));
    qDebug() << endl << "Дисциплины: " << endl;
    for (auto e : this->repoSubjects.getAll()) {
        qDebug() << e.toString() << endl;
    }

    qDebug() << "Удаление элемента 'Измененный элемент'" << endl;
    this->repoSubjects.remove(4);
    qDebug() << endl << "Дисциплины: " << endl;
    for (auto e : this->repoSubjects.getAll()) {
        qDebug() << e.toString() << endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addSubjectButton_clicked()
{
    list_s->append("");
    this->repoSubjects.add(Subject(""));
    StringListModel *model = new StringListModel(*list_s);
    ui->subject_table->setModel(model);
    ui->subject_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void MainWindow::on_removeSubjectButton_clicked()
{
    int index =ui->subject_table->selectionModel()->currentIndex().row();
    this->repoSubjects.remove(index);
    list_s->removeAt(index);
    ui->subject_table->model()->removeRow(index);

}

void MainWindow::on_confirmSubjectButton_clicked()
{
    int index = ui->subject_table->selectionModel()->currentIndex().row();
    QVariant value = ui->subject_table->selectionModel()->currentIndex().data();
    QString str = value.toString();
    this->repoSubjects.update(index,str);
    list_s->replace(index,str);
}

void MainWindow::on_addGroupButton_clicked()
{
    list_gr->append("");
    this->repoGroupStudents.add(GroupStudents(""));
    StringListModel *model = new StringListModel(*list_gr);
    ui->group_table->setModel(model);
    ui->group_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_removeGroupButton_clicked()
{
    int index =ui->group_table->selectionModel()->currentIndex().row();
    this->repoGroupStudents.remove(index);
    list_gr->removeAt(index);
    ui->group_table->model()->removeRow(index);
}

void MainWindow::on_confirmGroupButton_clicked()
{
    int index = ui->group_table->selectionModel()->currentIndex().row();
    QVariant value = ui->group_table->selectionModel()->currentIndex().data();
    QString str = value.toString();
    this->repoGroupStudents.update(index,str);
    list_gr->replace(index,str);
}

void MainWindow::on_addCabinetsButton_clicked()
{
    list_cb->append("");
    StringListModel *model = new StringListModel(*list_cb);
    ui->cabinets_table->setModel(model);
    ui->cabinets_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_removeCabinetsButton_clicked()
{
    int r =ui->cabinets_table->selectionModel()->currentIndex().row();
    list_cb->removeAt(r);
    ui->cabinets_table->model()->removeRow(r);
}

void MainWindow::on_confirmCabinetsButton_clicked()
{
    int index = ui->cabinets_table->selectionModel()->currentIndex().row();
    QVariant value = ui->cabinets_table->selectionModel()->currentIndex().data();
    QString str = value.toString();
    list_cb->replace(index,str);
}

void MainWindow::on_addTimeButton_clicked()
{
    list_tm->append("");
    StringListModel *model = new StringListModel(*list_tm);
    ui->time_table->setModel(model);
    ui->time_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_removeTimeButton_clicked()
{
    int r =ui->time_table->selectionModel()->currentIndex().row();
    list_tm->removeAt(r);
    ui->time_table->model()->removeRow(r);
}

void MainWindow::on_confirmTimeButton_clicked()
{
    int index = ui->time_table->selectionModel()->currentIndex().row();
    QVariant value = ui->time_table->selectionModel()->currentIndex().data();
    QString str = value.toString();
    list_tm->replace(index,str);
}

void MainWindow::on_subject_table_clicked(const QModelIndex &index)
{
    //int in = ui->group_table->selectionModel()->currentIndex().row();

    // Переменные куда будем записывать значения (нужны для отладки)
    QList<Subject> subjects;
    Subject subject = Subject();

    // Добавляем различные преметы
    /*this->repoSubjects.add(Subject("АКЗ"));
    this->repoSubjects.add(Subject("РЯП"));
    this->repoSubjects.add(Subject("ООТРвПО"));
    this->repoSubjects.add(Subject("ВиАПО"));
    Subject sub = Subject();
    sub =this->repoSubjects.getById(1);
    QString t = sub.name;
    qDebug()<<"Получить по id"<<t;
    // Получить все предметы*/
    subjects = this->repoSubjects.getAll();

    QStringList list_s;
    qDebug()<<"Вывод всех";
    for (auto it = subjects.begin(); it != subjects.end(); ++it) {
        subject = *it;
        qDebug() << subject.name;
    }


    /*QList<Subject> subjects;
    Subject subject = Subject();

    // Получить все предметы
    subjects = this->repoSubjects.getAll();

    QStringList list_s;

    for (auto it = subjects.begin(); it != subjects.end(); ++it) {
        subject = *it;
        qDebug() << subject.name;*/
    //}

}

void MainWindow::on_group_table_clicked(const QModelIndex &index)
{
    QList<Subject> group;
    Subject groups = Subject();
    group = this->repoSubjects.getAll();

    qDebug()<<"Вывод всех";
    for (auto it = group.begin(); it != group.end(); ++it) {
        groups = *it;
        qDebug() << groups.name;
    }

}

void MainWindow::on_saveFile_triggered()
{
    this->repoCabinets.save();
    this->repoSubjects.save();
    this->repoLessonsTimes.save();
    this->repoGroupStudents.save();
}
