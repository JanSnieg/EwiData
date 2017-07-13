#ifndef ADDKIEROWCA_H
#define ADDKIEROWCA_H

#include <QDialog>

namespace Ui {
class AddKierowca;
}

class AddKierowca : public QDialog
{
    Q_OBJECT

public:
    explicit AddKierowca(QWidget *parent = 0);
    ~AddKierowca();

private:
    Ui::AddKierowca *ui;
};

#endif // ADDKIEROWCA_H
