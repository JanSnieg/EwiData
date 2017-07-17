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
    int QueryPrepare();
    int KierowcaIdReturn();
    int GetLastId();
    void PrepareDialog();

private slots:
    int on_pushButtonOk_clicked();

    void on_pushButtonAnuluj_clicked();

private:
    Ui::AddKierowca *ui;

};

#endif // ADDKIEROWCA_H
