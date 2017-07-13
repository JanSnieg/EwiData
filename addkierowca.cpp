#include "addkierowca.h"
#include "ui_addkierowca.h"

AddKierowca::AddKierowca(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddKierowca)
{
    ui->setupUi(this);
}

AddKierowca::~AddKierowca()
{
    delete ui;
}
