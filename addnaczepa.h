#ifndef ADDNACZEPA_H
#define ADDNACZEPA_H

#include <QDialog>

namespace Ui {
class AddNaczepa;
}

class AddNaczepa : public QDialog
{
    Q_OBJECT

public:
    explicit AddNaczepa(QWidget *parent = 0);
    ~AddNaczepa();

private:
    Ui::AddNaczepa *ui;
};

#endif // ADDNACZEPA_H
