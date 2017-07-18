#ifndef ADDNACZEPA_H
#define ADDNACZEPA_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QString>
#include <QDate>
#include <addkierowca.h>            //This is for method getLastId()

namespace Ui {
class AddNaczepa;
}

class AddNaczepa : public QDialog
{
    Q_OBJECT

public:
    explicit AddNaczepa(QWidget *parent = 0);
    ~AddNaczepa();

    void PrepareDialog();               //Prepering DialogWindow, for example filling dateEdits with current date
    void QueryPrepare();                //Prepering Query for adding data to sql

private slots:
    void on_pushButtonOk_clicked();     //On "OK" button clicked adding everything filled to sql
    void on_pushButtonAnuluj_clicked(); //Just closing this window

private:
    Ui::AddNaczepa *ui;
};

#endif // ADDNACZEPA_H
