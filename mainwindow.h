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
#include "preferences.h"
#include "addkierowca.h"
#include "addciagnik.h"
#include "addnaczepa.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Preferences *PreferencesWindow;
    AddKierowca *addKierowcaWindow;
    AddCiagnik *addCiagnikWindow;
    AddNaczepa *AddNaczepaWindow;



private:
    Ui::MainWindow *ui;
    QString CreateTableKierowca();
    QString CreateTableCiagnik();
    QString CreateTableNaczepa();
    QString ConnectDatabase();             // Connecting to Database
    void MessageDatabase(QString); // and showing result in the MessageBox
    void NameHeaders(QSqlQuery);               // Seting QTableWidget headers names from Sql headers
    void FillTable(QSqlQuery);                // Function that prepare and fill QTableWighet for Sql data

    // Refreshing main QTableWidget
    QSqlQuery PrepareQuery();           // Funkction that prepare QSqlQuery for other funkcions

    void showAddKierowcaWindow();
    void showAddCiagnikWindow();
    void showAddNaczepaWindow();

public slots:
    void Add();
    void showPreferencesWindow();
};

#endif // MAINWINDOW_H
