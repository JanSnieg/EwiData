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

    std::vector<QSqlQuery> mainQueryVector; //Vector that holds three queries from sql
    int mainColumn ;                        //Intiger that is used in FillTable() method to know from where filling should start

    void setMainColumn();                   //Setting mainColumn intiget to 0
    void setMainColumn(int);                //Method that takes int that is then added to mainColumn intiger
    void on_Button_Refresh_clicked();       //Uses Refreshing method

    void Refreshing();                      //Main method to refresh connection, and mainWindow QTableWidget
    QString ConnectDatabase();              //Connecting to Database using vector from Preferences class
    void MessageDatabase(QString);          //and showing information about connection in the MessageBox
    void PrepareQuery(QString);                    //Method that prepare QSqlQuery for other funkcions
    void FillTable(QSqlQuery);              //Function that prepare and fill QTableWighet for Sql data and seting QTableWidget headers names from Sql headers

    QString CreateTableKierowca();          //Creating table kierowca if not exists in sql
    QString CreateTableCiagnik();           //Creating table ciagnik if not exists in sql
    QString CreateTableNaczepa();           //Creating table naczepa if not exists in sql

    void showAddKierowcaWindow();           //Methods that shows specyfic Dialog windows
    void showAddCiagnikWindow();
    void showAddNaczepaWindow();

private slots:
    void Add();                             //Opens MessegeBox that ask you what do you whant to add to database
    void showPreferencesWindow();           //Shows Preferences Dialog window
    void on_comboBox_Sort_activated(const QString &arg1);
};

#endif // MAINWINDOW_H
