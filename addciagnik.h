#ifndef ADDCIAGNIK_H
#define ADDCIAGNIK_H

#include <QDialog>

namespace Ui {
class AddCiagnik;
}

class AddCiagnik : public QDialog
{
    Q_OBJECT

public:
    explicit AddCiagnik(QWidget *parent = 0);
    ~AddCiagnik();

private:
    Ui::AddCiagnik *ui;
};

#endif // ADDCIAGNIK_H
