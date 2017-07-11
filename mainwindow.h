#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QMessageBox>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlDatabase DatabaseConnect();     // Connecting to Database and showing result tin MessageBox
    void Refresh(QSqlDatabase);         // Refreshing main QTableWidget
    void TableFilling();                // Function that prepare QTableWighet for Sql data and seting headers from sql headers
    QSqlQuery QueryPrepere();           // Funkction that prepare QSqlQuery for other funkcions
};

#endif // MAINWINDOW_H
