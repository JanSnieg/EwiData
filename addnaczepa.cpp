#include "addnaczepa.h"
#include "ui_addnaczepa.h"

AddNaczepa::AddNaczepa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNaczepa)
{
    ui->setupUi(this);
    PrepareDialog();
}

AddNaczepa::~AddNaczepa()                           { delete ui; }

void AddNaczepa::on_pushButtonOk_clicked()          { QueryPrepare(); }
void AddNaczepa::on_pushButtonAnuluj_clicked()      { this->close(); }

void AddNaczepa::PrepareDialog()
{
    AddKierowca kierowca;
    ui->dateEditOs3_2->setDate(QDate::currentDate());
    ui->dateEditOs4->setDate(QDate::currentDate());
    ui->dateEditOs5->setDate(QDate::currentDate());
    ui->dateEditPrzeglad->setDate(QDate::currentDate());
    ui->dateEditTachograf->setDate(QDate::currentDate());
    ui->spinBoxIdKierowca->setValue(kierowca.GetLastId());
}

void AddNaczepa::QueryPrepare()
{
    QSqlQuery addNaczepaQuery;
    addNaczepaQuery.prepare("INSERT INTO EwiData.naczepa (NumerRejNaczepa, DataPrzegladuNaczepa, "
                            "Os3, DataOsi3, Os4, DataOsi4, Os5, DataOsi5, kierowcaID)"
                             "VALUES (?,?,?,?,?,?,?,?,?)");
    addNaczepaQuery.addBindValue(ui->lineEditNumerRej->text());
    addNaczepaQuery.addBindValue(ui->dateEditPrzeglad->date());
    addNaczepaQuery.addBindValue(ui->lineEditOs3_2->text().toInt());
    addNaczepaQuery.addBindValue(ui->dateEditOs3_2->date());
    addNaczepaQuery.addBindValue(ui->lineEditOs4->text().toInt());
    addNaczepaQuery.addBindValue(ui->dateEditOs4->date());
    addNaczepaQuery.addBindValue(ui->lineEditOs5->text().toInt());
    addNaczepaQuery.addBindValue(ui->dateEditOs5->date());
    addNaczepaQuery.addBindValue(ui->spinBoxIdKierowca->text().toInt());
    if (!addNaczepaQuery.exec())
        QMessageBox::warning(NULL, addNaczepaQuery.lastQuery(), addNaczepaQuery.lastError().text(), QMessageBox::Ok);
    else
    {
        QMessageBox::information(NULL, "Dodano", "Wpisane dane dodane do Bazy danych", QMessageBox::Ok);
        this->close();
    }
    this->close();
}
