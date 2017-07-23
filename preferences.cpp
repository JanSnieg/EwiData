#include "preferences.h"
#include "ui_preferences.h"


Preferences::Preferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);
    DialogPrepare();
}

Preferences::~Preferences()                         { delete ui; }

void Preferences::setVectorValues()
{
    for (int i = 0; i < 4; i++)
    mainPreferancesVector.push_back("");
}

void Preferences::on_pushButtonAnuluj_clicked()     { this->close(); }
void Preferences::on_pushButtonOk_clicked()         { saveIntoFile(); this->close(); }

void Preferences::DialogPrepare()
{
    openFromFile();
    ui->lineEditHos->setText(mainPreferancesVector[0]);
    ui->lineEditDatabase->setText(mainPreferancesVector[1]);
    ui->lineEditUser->setText(mainPreferancesVector[2]);
    ui->lineEditPassword->setText(mainPreferancesVector[3]);
}

void Preferences::openFromFile()
{
    setVectorValues();
    int lineCount = 0;
    std::string line;
    std::ifstream preferencesFile;
    preferencesFile.open("preferencesFile.txt");
    if (preferencesFile.is_open())
    {
        while (std::getline(preferencesFile, line))
        {
            mainPreferancesVector[lineCount] = (QString::fromStdString(line));
            lineCount++;
        }
    }
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
