#ifndef ADDCIAGNIK_H
#define ADDCIAGNIK_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QString>
#include <QDate>
#include <addkierowca.h>


namespace Ui {
class AddCiagnik;
}

class AddCiagnik : public QDialog
{
    Q_OBJECT

public:
    explicit AddCiagnik(QWidget *parent = 0);
    ~AddCiagnik();
    void QueryPrepare();
    void PrepareDialog();
    int GetLastId();

private slots:
    void on_pushButtonOk_clicked();

    void on_pushButtonAnuluj_clicked();

private:
    Ui::AddCiagnik *ui;
};

#endif // ADDCIAGNIK_H
