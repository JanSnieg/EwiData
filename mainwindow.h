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
#include <QPushButton>
#include <QColor>
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
    QSqlDatabase database;
    bool bFirstTime;

private:
    Ui::MainWindow *ui;

    void setDatabase();
    void openDatabase();
    void closeDatabase();

    QString ConnectDatabase();              //Connecting to Database using vector from Preferences class
    void MessageDatabase(QString);          //and showing information about connection in the MessageBox
    void PrepareQuery(QString);             //Method that prepare QSqlQuery for other funkcions
    void FillTable(QSqlQuery);              //Method that prepare and fill QTableWighet for Sql data and seting QTableWidget headers names from Sql headers
    QColor IsDateOk(QDate);                 //Method that cheks all Date data from sql, and returns QColor that is used below
    bool ColorTable(QSqlQuery, int, int);   //Colors table with colors from IsDateOk();

    QString CreateTableKierowca();          //Creating table kierowca if not exists in sql
    QString CreateTableCiagnik();           //Creating table ciagnik if not exists in sql
    QString CreateTableNaczepa();           //Creating table naczepa if not exists in sql

    void showAddKierowcaWindow();           //Methods that shows specyfic Dialog windows
    void showAddCiagnikWindow();
    void showAddNaczepaWindow();


private slots:
    void Add();                             //Opens MessegeBox that ask you what do you whant to add to database
    void showPreferencesWindow();           //Shows Preferences Dialog window
    void OrderBy();                         //Main 'refresh' method that is used almost everywhere
    void EditDatabaseRecord(int, int);      //Method to edit Database record, is updates evertime you change current item value
    void DeleteRecord();                    //Deletes all values in current row
};

#endif // MAINWINDOW_H
