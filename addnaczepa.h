#ifndef ADDNACZEPA_H
#define ADDNACZEPA_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QString>
#include <QDate>
#include <addkierowca.h>

namespace Ui {
class AddNaczepa;
}

class AddNaczepa : public QDialog
{
    Q_OBJECT

public:
    explicit AddNaczepa(QWidget *parent = 0);
    ~AddNaczepa();
    void QueryPrepare();
    void PrepareDialog();


private slots:
    void on_pushButtonOk_clicked();

    void on_pushButtonAnuluj_clicked();

private:
    Ui::AddNaczepa *ui;
};

#endif // ADDNACZEPA_H
