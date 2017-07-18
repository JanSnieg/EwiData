#ifndef ADDKIEROWCA_H
#define ADDKIEROWCA_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QString>
#include <QDate>
#include <QSqlResult>

namespace Ui {
class AddKierowca;
}

class AddKierowca : public QDialog
{
    Q_OBJECT

public:
    explicit AddKierowca(QWidget *parent = 0);
    ~AddKierowca();
    void PrepareDialog();               //Prepering DialogWindow, for example filling dateEdits with current date
    void QueryPrepare();                //Prepering Query for adding data to sql
    int GetLastId();                    //This method is used in AddCiagniik, and AddNaczepa to fill last inserted kierowcaID in spinBoxes

private slots:
    void on_pushButtonOk_clicked();     //On "OK" button clicked adding everything filled to sql
    void on_pushButtonAnuluj_clicked(); //Just closing this window

private:
    Ui::AddKierowca *ui;
};

#endif // ADDKIEROWCA_H
