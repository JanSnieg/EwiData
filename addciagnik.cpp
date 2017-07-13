#include "addciagnik.h"
#include "ui_addciagnik.h"

AddCiagnik::AddCiagnik(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCiagnik)
{
    ui->setupUi(this);
}

AddCiagnik::~AddCiagnik()
{
    delete ui;
}
