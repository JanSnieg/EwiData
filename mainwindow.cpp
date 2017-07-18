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

void MainWindow::setMainColumn()                { mainColumn = 0; }
void MainWindow::setMainColumn(int column)      { mainColumn += column; }
void MainWindow::on_Button_Refresh_clicked()    { Refreshing(); }

void MainWindow::Refreshing()
{
    setMainColumn();
    MessageDatabase(ConnectDatabase());
    onC
}

QString MainWindow::ConnectDatabase()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
    Preferences pref;
    std::vector <QString> preferencesVector = pref.openFromFile();

    database.setHostName(preferencesVector[0]);
    database.setDatabaseName(preferencesVector[1]);
    database.setUserName(preferencesVector[2]);
    database.setPassword(preferencesVector[3]);

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

void MainWindow::PrepareQuery(QString orderByString)
{
    // TODO Make sort by Name etc.
    QSqlQuery kierowca ("SELECT Imie, Nazwisko, NumerDowodu, Pesel FROM ewidata.kierowca ORDER BY " + orderByString);
    QSqlQuery ciagnik ("SELECT NumerRej FROM ewidata.ciagnik ORDER BY " + orderByString);
    QSqlQuery naczepa ("SELECT NumerRej FROM ewidata.naczepa ORDER BY " + orderByString);
    mainQueryVector.push_back(kierowca);
    mainQueryVector.push_back(ciagnik);
    mainQueryVector.push_back(naczepa);

    for (int queryCount = 0; queryCount<3; queryCount++)
    {
        QMessageBox::warning(NULL,"For!", "queryCount: " + QString(queryCount),QMessageBox::Ok);
        if (mainQueryVector[queryCount].isValid())
        {
            mainQueryVector[queryCount].exec();
            FillTable(mainQueryVector[queryCount]);
        }
        else
            QMessageBox::warning(NULL,"Query not Valid!", mainQueryVector[queryCount].lastError().text(),QMessageBox::Ok);
    }
}

void MainWindow::FillTable(QSqlQuery query)
{
    ui->tableWidget_Main->setRowCount(query.size());
    ui->tableWidget_Main->setColumnCount(6);
    int row = 0;
    for (int columnCount = mainColumn; columnCount<query.record().count(); columnCount++)
        ui->tableWidget_Main->setHorizontalHeaderItem(columnCount, new QTableWidgetItem(query.record().fieldName(columnCount)));
    // Filling QTableWidget with data from Sql
    while (query.next())
    {
        for (int columnCount = mainColumn; columnCount<query.record().count(); columnCount++)
            ui->tableWidget_Main->setItem(row, columnCount, new QTableWidgetItem(query.value(columnCount).toString()));
        row++;
    }
    setMainColumn(query.size());
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
    QSqlQuery mainQuery("CREATE TABLE IF NOT EXISTS ewidata.ciagnik(NumerRej VARCHAR (20) UNIQUE , "
                        "DataPrzegladu DATE, DataTachografu DATE, "
                        "Os1 INT, DataOsi1 DATE, Os2 INT, DataOsi2 DATE, "
                        "ciagnikID INT AUTO_INCREMENT, kierowcaID INT,"
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
    QSqlQuery mainQuery("CREATE TABLE IF NOT EXISTS ewidata.naczepa(NumerRej VARCHAR (20) UNIQUE, "
                        "DataPrzegladu DATE, "
                        "Os1 INT, DataOsi1 DATE, Os2 INT, DataOsi2 DATE, Os3 INT, DataOsi3 DATE, "
                        "naczepaID INT AUTO_INCREMENT, kierowcaID INT,"
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

void MainWindow::on_comboBox_Sort_activated(const QString &arg1)
{
    if (arg1 == "Nazwisko")
        PrepareQuery("Nazwisko");
    else if (arg1 == "ID")
        PrepareQuery("kierowcaID");
    else if (arg1 == "Pesel")
        PrepareQuery("Pesel");
}
