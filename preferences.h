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

    void DialogPrepare(std::vector<QString>);   //Opens file, and fill lineEdits with data from there
    std::vector <QString> openFromFile();       //Method that open preferences from preferencesFile and returnig vector filled with preferances
                                                //Used in mainWindow::ConnectDatabase() method
    void saveIntoFile();                        //Method to save filled preferances into preferencesFile.txt

private slots:
    void on_pushButtonAnuluj_clicked();         //Closes window without saving anything
    void on_pushButtonOk_clicked();             //Saves filled preferences into file

private:
    Ui::Preferences *ui;
};

#endif // PREFERENCES_H
