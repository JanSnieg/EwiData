#include "preferences.h"
#include "ui_preferences.h"


Preferences::Preferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);
}

Preferences::~Preferences()
{
    delete ui;
}

std::vector<QString> Preferences::openFromFile()
{
    std::string line;
    std::vector <QString> preferencesVector;
    std::fstream preferencesFile;
    preferencesFile.open("preferencesFile.txt");
    if (preferencesFile.is_open())
    {
        while (std::getline(preferencesFile, line))
            preferencesVector.push_back(QString::fromStdString(line));
    }
    return preferencesVector;
}

void Preferences::saveIntoFile()
{
    std::fstream preferencesFile;
    preferencesFile.open("preferencesFile.txt");
    if (preferencesFile.is_open())
    {
        preferencesFile << ui->lineEditHos;
        preferencesFile << ui->lineEditDatabase;
        preferencesFile << ui->lineEditUser;
        preferencesFile << ui->lineEditPassword;
        QMessageBox::information(NULL, "Informacja", "Plik z ustawieniami został zapisany", QMessageBox::Ok);
    }
    else
        QMessageBox::warning(NULL, "UWAGA!", "Plik z ustawieniami nie został otwarty", QMessageBox::Ok);
    preferencesFile.close();
}

bool Preferences::on_pushButtonOk_clicked()
{
    saveIntoFile();
    this->close();
    return true;
}

void Preferences::on_pushButtonAnuluj_clicked()
{
    this->close();
}
