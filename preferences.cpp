#include "preferences.h"
#include "ui_preferences.h"


Preferences::Preferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);
    DialogPrepare(openFromFile());
}

Preferences::~Preferences()                         { delete ui; }

void Preferences::on_pushButtonAnuluj_clicked()     { this->close(); }
void Preferences::on_pushButtonOk_clicked()         { saveIntoFile(); this->close(); }

void Preferences::DialogPrepare(std::vector<QString> preferencesVector)
{
    ui->lineEditHos->setText(preferencesVector[0]);
    ui->lineEditDatabase->setText(preferencesVector[1]);
    ui->lineEditUser->setText(preferencesVector[2]);
    ui->lineEditPassword->setText(preferencesVector[3]);
}

std::vector<QString> Preferences::openFromFile()
{
    std::string line;
    std::vector <QString> preferencesVector;
    std::ifstream preferencesFile;
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
    std::ofstream preferencesFile;
    preferencesFile.open("preferencesFile.txt");
    if (preferencesFile.is_open())
    {
        preferencesFile << ui->lineEditHos->text().toStdString() << std::endl;
        preferencesFile << ui->lineEditDatabase->text().toStdString() << std::endl;
        preferencesFile << ui->lineEditUser->text().toStdString() << std::endl;
        preferencesFile << ui->lineEditPassword->text().toStdString() << std::endl;
        QMessageBox::information(NULL, "Informacja", "Plik z ustawieniami został zapisany", QMessageBox::Ok);
        preferencesFile.close();
    }
    else
        QMessageBox::warning(NULL, "UWAGA!", "Plik z ustawieniami nie został otwarty", QMessageBox::Ok);
}
