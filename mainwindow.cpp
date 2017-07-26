#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setDatabase();
    OrderBy();
    connect(ui->actionUstawiania, SIGNAL(triggered()), this, SLOT(showPreferencesWindow()));
    connect(ui->actionDodaj, SIGNAL(triggered(bool)), this, SLOT(Add()));
    connect(ui->comboBox_Sort, SIGNAL(currentIndexChanged(QString)), this, SLOT(OrderBy()));
    connect(ui->tableWidget_Main, SIGNAL(cellChanged(int,int)), this, SLOT(EditDatabaseRecord(int, int)));
    connect(ui->pushButtonDelete, SIGNAL(clicked(bool)), this, SLOT(DeleteRecord()));
}

MainWindow::~MainWindow()                       { delete ui; }

void MainWindow::setDatabase()                  { database = QSqlDatabase::addDatabase("QMYSQL"); }

void MainWindow::openDatabase()                 { database.open(); }
void MainWindow::closeDatabase()                { database.close(); }

QString MainWindow::ConnectDatabase()
{
    Preferences pref;
    pref.openFromFile();

    database.setHostName(pref.mainPreferancesVector[0]);
    database.setDatabaseName(pref.mainPreferancesVector[1]);
    database.setUserName(pref.mainPreferancesVector[2]);
    database.setPassword(pref.mainPreferancesVector[3]);

    if (database.isValid())
        return "Połączono!\n";
    else
      return "Database Error: " + database.lastError().text();
    return 0;
}

void MainWindow::MessageDatabase(QString message)
{
    if (bFirstTime)
    {
        QMessageBox mBox;
        mBox.setText("Database information");
        mBox.setInformativeText(message);
        mBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
        mBox.setDefaultButton(QMessageBox::Ok);
        int ret = mBox.exec();
        switch (ret)
        {
        case QMessageBox::Ok:
            openDatabase();
            break;
        case QMessageBox::Cancel:
            closeDatabase();
            break;
        default:
            break;
        }
        bFirstTime = false;
    }
    else
        openDatabase();
}

void MainWindow::OrderBy()
{
    MessageDatabase(ConnectDatabase());
    PrepareQuery(ui->comboBox_Sort->currentText());
    closeDatabase();
}

void MainWindow::PrepareQuery(QString SOrderBy)
{
    if (database.isOpen())
    {
        QSqlQuery mainQuery("SELECT * FROM kierowca "
                            "LEFT JOIN ciagnik ON ciagnik.kierowcaID = kierowca.kierowcaID "
                            "LEFT JOIN naczepa ON naczepa.kierowcaID = kierowca.kierowcaID "
                            "ORDER BY kierowca." + SOrderBy);
        ui->tableWidget_Main->blockSignals(true);
        if (mainQuery.exec())
        {
            FillTable(mainQuery);
        }
        else
        {
            QMessageBox::warning(NULL,"Query not Valid!",mainQuery.lastError().text(), QMessageBox::Ok);
            CreateTableKierowca();
            CreateTableCiagnik();
            CreateTableNaczepa();
        }
        ui->tableWidget_Main->blockSignals(false);
    }
    else
        QMessageBox::warning(NULL, "Database not opened", database.lastError().text(), QMessageBox::Ok);
}

void MainWindow::FillTable(QSqlQuery query)
{
    ui->tableWidget_Main->setRowCount(query.size());
    ui->tableWidget_Main->setColumnCount(query.record().count());
    int row = 0;
    for (int columnCount = 0; columnCount<query.record().count(); columnCount++)
    {
        ui->tableWidget_Main->setHorizontalHeaderItem(columnCount, new QTableWidgetItem(query.record().fieldName(columnCount)));
        ui->tableWidget_Main->horizontalHeader()->setStretchLastSection(true);
    }
    // Filling QTableWidget with data from Sql
    while (query.next())
    {
        for (int columnCount = 0; columnCount<query.record().count(); columnCount++)
        {
            ui->tableWidget_Main->setItem(row, columnCount, new QTableWidgetItem(query.value(columnCount).toString()));
            if (ColorTable(query, columnCount, row))
                ui->tableWidget_Main->item(row, 0)->setBackground(QColor::fromRgb(255,153,153));

        }
        row++;
    }
    ui->tableWidget_Main->setVisible(false);
    ui->tableWidget_Main->resizeColumnsToContents();
    ui->tableWidget_Main->setVisible(true);
}

QColor MainWindow::IsDateOk(QDate dateFromSql)
{
    if (QDate::currentDate().daysTo(dateFromSql) < 8)
        return QColor::fromRgb(204,0,0);
    else if (QDate::currentDate().daysTo(dateFromSql) < 15)
        return QColor::fromRgb(204,102,0);
    else if (QDate::currentDate().daysTo(dateFromSql) < 30)
        return QColor::fromRgb(204,204,0);
    else
        return QColor::fromRgb(255,255,255);
}

bool MainWindow::ColorTable(QSqlQuery query, int columnCount, int row)
{

    if (query.value(columnCount).toDate().isValid())
    {
        if (ui->tableWidget_Main->horizontalHeaderItem(columnCount)->text() == "DataOsi1" ||
                ui->tableWidget_Main->horizontalHeaderItem(columnCount)->text() == "DataOsi2" ||
                ui->tableWidget_Main->horizontalHeaderItem(columnCount)->text() == "DataOsi3" ||
                ui->tableWidget_Main->horizontalHeaderItem(columnCount)->text() == "DataOsi4" ||
                ui->tableWidget_Main->horizontalHeaderItem(columnCount)->text() == "DataOsi5" ||
                ui->tableWidget_Main->horizontalHeaderItem(columnCount)->text() == "DataPrzyjecia")
        {
            ui->tableWidget_Main->item(row, columnCount)->setBackground(QColor::fromRgb(255,255,255));
            return false;
        }
        else
        {
            ui->tableWidget_Main->item(row, columnCount)->setBackground(IsDateOk(query.value(columnCount).toDate()));
            return true;
        }
    }
    return false;
}


QString MainWindow::CreateTableKierowca()
{
    QSqlQuery mainQuery("CREATE TABLE IF NOT EXISTS ewidata.kierowca(kierowcaID INT UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT, "
                        "Imie VARCHAR(20) NOT NULL, Nazwisko VARCHAR(20) NOT NULL, "
                        "NumerDowodu VARCHAR (20) UNIQUE NOT NULL, DataPrzyjecia DATE, DataPrawoJazdy DATE, "
                        "DataADR DATE)");
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
    QSqlQuery mainQuery("CREATE TABLE IF NOT EXISTS ewidata.ciagnik(NumerRejCiagnik VARCHAR (20) UNIQUE , "
                        "DataPrzegladuCiagnik DATE, DataTachografu DATE, CzytanieTachografu DATE, UbezpieczenieCiagnik DATE, "
                        "Os1 INT, DataOsi1 DATE, Os2 INT, DataOsi2 DATE, "
                        "ciagnikID INT AUTO_INCREMENT, kierowcaID INT,"
                        "PRIMARY KEY (ciagnikID), "
                        "FOREIGN KEY (kierowcaID) REFERENCES kierowca(kierowcaID) "
                        "ON DELETE CASCADE "
                        "ON UPDATE CASCADE)");
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
    QSqlQuery mainQuery("CREATE TABLE IF NOT EXISTS ewidata.naczepa(NumerRejNaczepa VARCHAR (20) UNIQUE, "
                        "DataPrzegladuNaczepa DATE, UbezpieczenieNaczepa DATE, "
                        "Os3 INT, DataOsi3 DATE, Os4 INT, DataOsi4 DATE, Os5 INT, DataOsi5 DATE, "
                        "naczepaID INT AUTO_INCREMENT, kierowcaID INT,"
                        "PRIMARY KEY (naczepaID), "
                        "FOREIGN KEY (kierowcaID) REFERENCES kierowca(kierowcaID) "
                        "ON DELETE CASCADE "
                        "ON UPDATE CASCADE)");
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
    closeDatabase();
}

void MainWindow::showAddCiagnikWindow()
{
    addCiagnikWindow = new AddCiagnik(this);
    addCiagnikWindow->show();
    addCiagnikWindow->exec();
    closeDatabase();
}

void MainWindow::showAddNaczepaWindow()
{
    AddNaczepaWindow = new AddNaczepa(this);
    AddNaczepaWindow->show();
    AddNaczepaWindow->exec();
    closeDatabase();
}

void MainWindow::showPreferencesWindow()
{
    PreferencesWindow = new Preferences(this);
    PreferencesWindow->show();
    PreferencesWindow->exec();
    closeDatabase();
}

void MainWindow::Add()
{
    openDatabase();
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
    {
        showAddKierowcaWindow();
        Add();
    }
    else if (mBox.clickedButton() == addCiagnikButton)
    {
        showAddCiagnikWindow();
        Add();
    }
    else if (mBox.clickedButton() == addNaczepaButton)
    {
        showAddNaczepaWindow();
        Add();
    }
    closeDatabase();
    OrderBy();
}

void MainWindow::EditDatabaseRecord(int row, int column)
{
    openDatabase();
    if (database.isOpen())
    {
        QSqlQuery EditData("UPDATE kierowca "
                           "LEFT JOIN ciagnik ON ciagnik.kierowcaID = kierowca.kierowcaID "
                           "LEFT JOIN naczepa ON naczepa.kierowcaID = kierowca.kierowcaID "
                           "SET " + ui->tableWidget_Main->horizontalHeaderItem(column)->text() + " = '"
                           + ui->tableWidget_Main->item(row, column)->text() + "' WHERE kierowca.kierowcaID = " + ui->tableWidget_Main->item(row,0)->text());
        if (EditData.exec())
        {
            QMessageBox::information(NULL, "Update info", "Edytowano rekord w bazie danych", QMessageBox::Ok);
        }
        else
            QMessageBox::warning(NULL, "Update Error", EditData.lastError().text(), QMessageBox::Ok);
        closeDatabase();
     }
    else
        QMessageBox::warning(NULL, "Database Error", database.lastError().text(), QMessageBox::Ok);
    OrderBy();
}

void MainWindow::DeleteRecord()
{
    openDatabase();
    QSqlQuery DeleteData("DELETE kierowca FROM kierowca "
                         "WHERE kierowcaID = " + ui->tableWidget_Main->item(ui->tableWidget_Main->currentRow(),0)->text());
    if (DeleteData.exec())
        QMessageBox::information(NULL,"Delete info", "Record został usunięty",QMessageBox::Ok);
    else
        QMessageBox::warning(NULL, "Delete Error", DeleteData.lastError().text(), QMessageBox::Ok);
    closeDatabase();
    OrderBy();
}
