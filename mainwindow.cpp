#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Refreshing();
    connect(ui->actionUstawiania, SIGNAL(triggered()), this, SLOT(showPreferencesWindow()));
    connect(ui->actionDodaj, SIGNAL(triggered(bool)), this, SLOT(Add()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Refreshing()
{
    MessageDatabase(ConnectDatabase());

    FillTable(PrepareQuery());
}

QString MainWindow::ConnectDatabase()
{
    // TODO Make Alaviability to change Database things
    QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
//    Preferences pref;
//    std::vector <QString> preferencesVector = pref.openFromFile();

//    database.setHostName(preferencesVector[1]);
//    database.setDatabaseName(preferencesVector[2]);
//    database.setUserName(preferencesVector[3]);
//    database.setPassword(preferencesVector[4]);

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

void MainWindow::NameHeaders(QSqlQuery mainQuery)
{
    ui->tableWidget_Main->setRowCount(mainQuery.size());
    ui->tableWidget_Main->setColumnCount(mainQuery.record().count());
    // Setting headers names from sql to QTableWidget
    for (int columnCount = 0; columnCount<mainQuery.record().count(); columnCount++)
         ui->tableWidget_Main->setHorizontalHeaderItem(columnCount, new QTableWidgetItem(mainQuery.record().fieldName(columnCount)));
}

void MainWindow::FillTable(QSqlQuery mainQuery)
    {
    NameHeaders(mainQuery);
    int row =0;
    // Filling QTableWidget with data from Sql
    while (mainQuery.next())
    {
        for (int column = 0; column<mainQuery.record().count(); column++)
        {
            ui->tableWidget_Main->setItem(row, column, new QTableWidgetItem(mainQuery.value(column).toString()));
        }
        ui->tableWidget_Main->resizeColumnsToContents();
    }
}

QSqlQuery MainWindow::PrepareQuery()
{
    // TODO Make sort by Name etc.
    QSqlQuery mainQuery("SELECT kierowca.Imie, kierowca.Nazwisko, kierowca.NumerDowodu, kierowca.Pesel, "
                        "ciagnik.NumerRej, naczepa.NumerRej "
                        "FROM ewidata.kierowca, ewidata.ciagnik, ewidata.naczepa");
//    QSqlQuery mainQuery("SELECT * FROM ewidata.kierowca");
    if (!mainQuery.exec())
    {
        MessageDatabase(CreateTableKierowca());
        MessageDatabase(CreateTableCiagnik());
        MessageDatabase(CreateTableNaczepa());
    }
    else
    {
        FillTable(mainQuery);
    }
    return mainQuery;
}

void MainWindow::Add()
{
    QMessageBox mBox;
    mBox.setText("Dodawanie");
    mBox.setInformativeText("Co chciałbyś dodać?");
    QPushButton *abortButton = mBox.addButton(tr("Anuluj"), QMessageBox::ActionRole);
    QPushButton *addKierowcaButton = mBox.addButton(tr("Kierowca") ,QMessageBox::ActionRole);
    QPushButton *addCiagnikButton = mBox.addButton(tr("Ciągnik"), QMessageBox::ActionRole);
    QPushButton *addNaczepaButton = mBox.addButton(tr("Naczepa"), QMessageBox::ActionRole);
    mBox.setDefaultButton(abortButton);

    mBox.exec();
    if (mBox.clickedButton() == abortButton)
        mBox.close();
    else if (mBox.clickedButton() == addKierowcaButton)
        showAddKierowcaWindow();
    else if (mBox.clickedButton() == addCiagnikButton)
        showAddCiagnikWindow();
    else if (mBox.clickedButton() == addNaczepaButton)
        showAddNaczepaWindow();

}

void MainWindow::showAddKierowcaWindow()
{
    addKierowcaWindow = new AddKierowca(this);
    addKierowcaWindow->show();
    addKierowcaWindow->exec();
}

void MainWindow::showAddCiagnikWindow()
{
    addCiagnikWindow = new AddCiagnik(this);
    addCiagnikWindow->show();
    addCiagnikWindow->exec();
}

void MainWindow::showAddNaczepaWindow()
{
    AddNaczepaWindow = new AddNaczepa(this);
    AddNaczepaWindow->show();
    AddNaczepaWindow->exec();
}

void MainWindow::showPreferencesWindow()
{
    PreferencesWindow = new Preferences(this);
    PreferencesWindow->show();
    PreferencesWindow->exec();
}

QString MainWindow::CreateTableKierowca()
{
    QSqlQuery mainQuery("CREATE TABLE IF NOT EXISTS ewidata.kierowca(kierowcaID INT UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT, "
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
                        "Os1 INT, DataOsi1 DATE, Os2 INT, DataOsi2 DATE, "
                        "ciagnikID INT NOT NULL AUTO_INCREMENT, kierowcaID INT,"
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
                        "DataPrzegladu DATE, "
                        "Os1 INT, DataOsi1 DATE, Os2 INT, DataOsi2 DATE, Os3 INT, DataOsi3 DATE, "
                        "naczepaID INT NOT NULL AUTO_INCREMENT, kierowcaID INT,"
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

void MainWindow::on_Button_Refresh_clicked()
{
    Refreshing();
}
