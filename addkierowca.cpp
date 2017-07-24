#include "addkierowca.h"
#include "ui_addkierowca.h"

AddKierowca::AddKierowca(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddKierowca)
{
    ui->setupUi(this);
    PrepareDialog();
}

AddKierowca::~AddKierowca()                     { delete ui; }

void AddKierowca::on_pushButtonOk_clicked()     { QueryPrepare(); }
void AddKierowca::on_pushButtonAnuluj_clicked() { this->close(); }

void AddKierowca::PrepareDialog()
{
    ui->dateEditAdr->setDate(QDate::currentDate());
    ui->dateEditPrawoJazdy->setDate(QDate::currentDate());
    ui->dateEditPrzyjecie->setDate(QDate::currentDate());
}

void AddKierowca::QueryPrepare()
{
    QSqlQuery addKierowcaQuery;
    addKierowcaQuery.prepare("INSERT INTO EwiData.kierowca (Imie, Nazwisko, NumerDowodu, DataPrzyjecia, DataPrawoJazdy, DataADR)"
                             "VALUES (?,?,?,?,?,?)");
    addKierowcaQuery.addBindValue(ui->lineEditImie->text());
    addKierowcaQuery.addBindValue(ui->lineEditNazwisko->text());
    addKierowcaQuery.addBindValue(ui->lineEditNumerDowodu->text());
    addKierowcaQuery.addBindValue(ui->dateEditPrzyjecie->date());
    addKierowcaQuery.addBindValue(ui->dateEditPrawoJazdy->text().toInt());
    addKierowcaQuery.addBindValue(ui->dateEditAdr->date());
    if (!addKierowcaQuery.exec())
        QMessageBox::warning(NULL, addKierowcaQuery.lastQuery(), addKierowcaQuery.lastError().text(), QMessageBox::Ok);
    else
    {
        QMessageBox::information(NULL, "Dodano", "Wpisane dane dodane do Bazy danych", QMessageBox::Ok);
    }
    this->close();
}

int AddKierowca::GetLastId()
{
    QSqlQuery lastIdQuery("SELECT kierowcaID FROM ewidata.kierowca ORDER BY kierowcaID DESC LIMIT 1");
    lastIdQuery.exec();
    while (lastIdQuery.next())
        return lastIdQuery.value(0).toInt();
    return 0;
}
