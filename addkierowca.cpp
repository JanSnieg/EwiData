#include "addkierowca.h"
#include "ui_addkierowca.h"

AddKierowca::AddKierowca(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddKierowca)
{
    ui->setupUi(this);
    PrepareDialog();
}

AddKierowca::~AddKierowca()
{
    delete ui;
}

int AddKierowca::QueryPrepare()
{
    QSqlQuery addKierowcaQuery;
    addKierowcaQuery.prepare("INSERT INTO EwiData.kierowca (Imie, Nazwisko, NumerDowodu, DataDowodu, Pesel, NumerADR, DataADR)"
                             "VALUES (?,?,?,?,?,?,?)");
    addKierowcaQuery.addBindValue(ui->lineEditImie->text());
    addKierowcaQuery.addBindValue(ui->lineEditNazwisko->text());
    addKierowcaQuery.addBindValue(ui->lineEditNumerDowodu->text());
    addKierowcaQuery.addBindValue(ui->dateEditDoowod->date());
    addKierowcaQuery.addBindValue(ui->lineEditPesel->text().toInt());
    addKierowcaQuery.addBindValue(ui->doubleSpinBoxAdr->text().toFloat());
    addKierowcaQuery.addBindValue(ui->dateEditAdr->date());
    if (!addKierowcaQuery.exec())
        QMessageBox::warning(NULL, addKierowcaQuery.lastQuery(), addKierowcaQuery.lastError().text(), QMessageBox::Ok);
    else
    {
        QMessageBox::information(NULL, "Dodano", "Wpisane dane dodane do Bazy danych", QMessageBox::Ok);
        this->close();
    }
    this->close();
}

int AddKierowca::GetLastId()
{
    QSqlQuery lastIdQuery("SELECT kierowcaID from ewidata.kierowca");
    return lastIdQuery.lastInsertId().toInt();

}

void AddKierowca::PrepareDialog()
{
    ui->dateEditAdr->setDate(QDate::currentDate());
    ui->dateEditDoowod->setDate(QDate::currentDate());
}

int AddKierowca::on_pushButtonOk_clicked()
{
   return QueryPrepare();
}



void AddKierowca::on_pushButtonAnuluj_clicked()
{
    this->close();
}
