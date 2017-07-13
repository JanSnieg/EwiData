#include "addnaczepa.h"
#include "ui_addnaczepa.h"

AddNaczepa::AddNaczepa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNaczepa)
{
    ui->setupUi(this);
}

AddNaczepa::~AddNaczepa()
{
    delete ui;
}
