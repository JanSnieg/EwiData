#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QApplication>
#include <QCoreApplication>

namespace Ui {
class Preferences;
}

class Preferences : public QDialog
{
    Q_OBJECT

public:
    explicit Preferences(QWidget *parent = 0);
    ~Preferences();


private:
    Ui::Preferences *ui;
};

#endif // PREFERENCES_H
