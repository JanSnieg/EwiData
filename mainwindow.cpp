#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase MainDatabase = DatabaseConnect();
    TableFilling();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QSqlDatabase MainWindow::DatabaseConnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.close();
    db.setHostName("localhost");
    db.setDatabaseName("EwiData");
    db.setUserName("root");
    db.setPassword("root");
    QMessageBox mBox;
    mBox.setText("Database information");
    if (db.isValid())
        mBox.setInformativeText("Connected");
    else
        mBox.setInformativeText("Database Error: " + db.lastError().text());
    mBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    mBox.setDefaultButton(QMessageBox::Ok);
    int ret = mBox.exec();
    switch (ret)
    {
    case QMessageBox::Ok:
        db.open();
        break;
    case QMessageBox::Cancel:
        db.close();
        break;
    default:
        break;
    }
    return db;
}

void MainWindow::Refresh(QSqlDatabase db)
{

}

void MainWindow::TableFilling()
{
    QSqlQuery kierowca = QueryPrepere();
    ui->tableWidget_Main->setRowCount(kierowca.size());
    ui->tableWidget_Main->setColumnCount(kierowca.record().count());
    int row =0;
    // Setting headers names from sql to QTableWidget
    for (int columnCount = 0; columnCount<kierowca.record().count(); columnCount++)
    {
         ui->tableWidget_Main->setHorizontalHeaderItem(columnCount, new QTableWidgetItem(kierowca.record().fieldName(columnCount)));
    }
    // Filling QTableWidget with data from Sql
    while (kierowca.next())
    {
        for (int column = 0; column<ui->tableWidget_Main->columnCount(); column++, row++)
        {
            ui->tableWidget_Main->setItem(row, column, new QTableWidgetItem(kierowca.value(column).toString()));
        }
        ui->tableWidget_Main->resizeColumnsToContents();
    }
}

QSqlQuery MainWindow::QueryPrepere()
{
    QSqlQuery kierowca("SELECT * FROM EwiData.kierowcy");
    kierowca.exec();
    return kierowca;
}


