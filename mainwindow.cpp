#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MessageDatabase(ConnectDatabase());
    //PrepareQuery("kierowca");
    PrepareQuery("ciagnik");
    //PrepareQuery("naczepa");
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::ConnectDatabase()
{
    // TODO Make Alaviability to change Database things
    QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setDatabaseName("EwiData");
    database.setUserName("root");
    database.setPassword("root");
    if (database.isValid())
    {
        database.open();
        return "Połączono!\n";
    }
    else
      return "Database Error: " + database.lastError().text();
}

void MainWindow::MessageDatabase(QString message)
{
    QMessageBox mBox;
    mBox.setText("Database information");
    mBox.setInformativeText(message);
    mBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    mBox.setDefaultButton(QMessageBox::Ok);
    int ret = mBox.exec();
    // TODO Make this buttons worth something
    switch (ret)
    {
    case QMessageBox::Ok:
        //database.open();
        break;
    case QMessageBox::Cancel:
        //database.close();
        break;
    default:
        break;
    }
}

void MainWindow::NameHeaders(QSqlQuery mainQuery, int numberOfColums)
{
    ui->tableWidget_Main->setRowCount(mainQuery.size());
    ui->tableWidget_Main->setColumnCount(numberOfColums);
    // Setting headers names from sql to QTableWidget
    for (int columnCount = 0; columnCount<mainQuery.record().count(); columnCount++)
         ui->tableWidget_Main->setHorizontalHeaderItem(columnCount, new QTableWidgetItem(mainQuery.record().fieldName(columnCount)));
}

void MainWindow::FillTable(QSqlQuery mainQuery, int numberOfColums)
    {
    NameHeaders(mainQuery, numberOfColums);
    int row =0;
    // Filling QTableWidget with data from Sql
    while (mainQuery.next())
    {
        for (int column = 0; column<numberOfColums; column++, row++)
        {
            ui->tableWidget_Main->setItem(row, column, new QTableWidgetItem(mainQuery.value(column).toString()));
        }
        ui->tableWidget_Main->resizeColumnsToContents();
    }
}

QSqlQuery MainWindow::PrepareQuery(QString tableName)
{
    QSqlQuery mainQuery("SELECT * FROM " + tableName);
    if (!mainQuery.exec())
    {
        if (tableName == "kierowca")
            MessageDatabase(CreateTableKierowca());
        else if (tableName == "ciagnik")
            MessageDatabase(CreateTableCiagnik());
        else if (tableName == "naczepa")
            MessageDatabase(CreateTableNaczepa());
    }
    else
    {
        if (tableName == "kierowca")
            FillTable(mainQuery, 7);
        else if (tableName == "ciagnik")
            FillTable(mainQuery, 7);
        else if (tableName == "naczepa")
            FillTable(mainQuery, 8);
    }
    return mainQuery;
}

QString MainWindow::CreateTableKierowca()
{
    QSqlQuery mainQuery("CREATE TABLE IF NOT EXISTS ewidata.kierowca(kierowcaID INT UNIQUE PRIMARY KEY NOT NULL, "
                        "Imie VARCHAR(20) NOT NULL, Nazwisko VARCHAR(20) NOT NULL, "
                        "NumerDowodu VARCHAR (20) UNIQUE NOT NULL, DataDowodu DATE, Pesel BIGINT UNIQUE NOT NULL, "
                        "NumerADR FLOAT(2), DataADR DATE)");
    if (mainQuery.isValid())
    {
        mainQuery.exec();
        return "Wszystko poszło dobrze!";
    }
    else
        return "Query error: " + mainQuery.lastError().text();
}

QString MainWindow::CreateTableCiagnik()
{
    QSqlQuery mainQuery("CREATE TABLE IF NOT EXISTS ewidata.ciagnik(NumerRej VARCHAR (20) UNIQUE NOT NULL, "
                        "DataPrzegladu DATE, DataTachografu DATE, "
                        "DataOsi1 DATE, DataOsi2 DATE, "
                        "ciagnikID INT NOT NULL, kierowcaID INT,"
                        "PRIMARY KEY (ciagnikID), "
                        "FOREIGN KEY (kierowcaID) REFERENCES kierowca(kierowcaID))");
    if (mainQuery.isValid())
    {
        mainQuery.exec();
        return "Wszystko poszło dobrze!";
    }
    else
        return "Query error: " + mainQuery.lastError().text();
}

QString MainWindow::CreateTableNaczepa()
{
    QSqlQuery mainQuery("CREATE TABLE IF NOT EXISTS ewidata.naczepa(NumerRej VARCHAR (20) UNIQUE NOT NULL, "
                        "DataPrzegladu DATE, DataTachografu DATE, "
                        "DataOsi1 DATE, DataOsi2 DATE, DataOsi3 DATE, "
                        "naczepaID INT NOT NULL, kierowcaID INT,"
                        "PRIMARY KEY (naczepaID), "
                        "FOREIGN KEY (kierowcaID) REFERENCES kierowca(kierowcaID))");
    if (mainQuery.isValid())
    {
        mainQuery.exec();
        return "Wszystko poszło dobrze!";
    }
    else
        return "Query error: " + mainQuery.lastError().text();
}
