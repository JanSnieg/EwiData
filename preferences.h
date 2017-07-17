#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <QMessageBox>

namespace Ui {
class Preferences;
}

class Preferences : public QDialog
{
    Q_OBJECT

public:
    explicit Preferences(QWidget *parent = 0);
    ~Preferences();
    void setPreferences();
    void saveIntoFile();
    std::vector <QString> openFromFile();

public slots:

    bool on_pushButtonOk_clicked();

private slots:
    void on_pushButtonAnuluj_clicked();

private:
    Ui::Preferences *ui;
};

#endif // PREFERENCES_H
