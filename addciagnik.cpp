#include "addciagnik.h"
#include "ui_addciagnik.h"

AddCiagnik::AddCiagnik(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCiagnik)
{
    ui->setupUi(this);
    PrepareDialog();
}

AddCiagnik::~AddCiagnik()                       { delete ui; }

void AddCiagnik::on_pushButtonOk_clicked()      { QueryPrepare(); }
void AddCiagnik::on_pushButtonAnuluj_clicked()  { this->close(); }

void AddCiagnik::PrepareDialog()
{
    AddKierowca kierowca;
    ui->spinBoxIdKierowca->setValue(kierowca.GetLastId());
    ui->dateEditOs1->setDate(QDate::currentDate());
    ui->dateEditOs2->setDate(QDate::currentDate());
    ui->dateEditPrzeglad->setDate(QDate::currentDate());
    ui->dateTachograf->setDate(QDate::currentDate());
    ui->dateEditCzytanie->setDate(QDate::currentDate());
    ui->dateEditUbezpieczenie->setDate(QDate::currentDate());
}

void AddCiagnik::QueryPrepare()
{
    QSqlQuery addCiagnikQuery;
    addCiagnikQuery.prepare("INSERT INTO EwiData.ciagnik (NumerRejCiagnik, DataPrzegladuCiagnik, "
                            "DataTachografu, CzytanieTachografu, UbezpieczenieCiagnik, "
                            "os1, DataOsi1, os2, DataOsi2, kierowcaID)"
                             "VALUES (?,?,?,?,?,?,?,?,?,?)");
    addCiagnikQuery.addBindValue(ui->lineEditNumerRej->text());
    addCiagnikQuery.addBindValue(ui->dateEditPrzeglad->date());
    addCiagnikQuery.addBindValue(ui->dateTachograf->date());
    addCiagnikQuery.addBindValue(ui->dateEditCzytanie->date());
    addCiagnikQuery.addBindValue(ui->dateEditUbezpieczenie->date());
    addCiagnikQuery.addBindValue(ui->lineEditOs1->text().toInt());
    addCiagnikQuery.addBindValue(ui->dateEditOs1->date());
    addCiagnikQuery.addBindValue(ui->lineEditOs2->text().toInt());
    addCiagnikQuery.addBindValue(ui->dateEditOs2->date());
    addCiagnikQuery.addBindValue(ui->spinBoxIdKierowca->text().toInt());
    if (!addCiagnikQuery.exec())
        QMessageBox::warning(NULL, addCiagnikQuery.lastQuery(), addCiagnikQuery.lastError().text(), QMessageBox::Ok);
    else
    {
        QMessageBox::information(NULL, "Dodano", "Wpisane dane dodane do Bazy danych", QMessageBox::Ok);
        this->close();
    }
    this->close();
}
