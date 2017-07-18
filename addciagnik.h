#ifndef ADDCIAGNIK_H
#define ADDCIAGNIK_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QString>
#include <QDate>
#include <addkierowca.h>                    //This is for method getLastId()


namespace Ui {
class AddCiagnik;
}

class AddCiagnik : public QDialog
{
    Q_OBJECT

public:
    explicit AddCiagnik(QWidget *parent = 0);
    ~AddCiagnik();
    void PrepareDialog();                   //Prepering DialogWindow, filling dates with current time etc.
    void QueryPrepare();                    //Prepering query to add Ciagnik

private slots:
    void on_pushButtonOk_clicked();         //When button "OK" is clicked SQL is adding data from lineEdits and dateEdit
    void on_pushButtonAnuluj_clicked();     //Just closing dialog

private:
    Ui::AddCiagnik *ui;
};

#endif // ADDCIAGNIK_H
