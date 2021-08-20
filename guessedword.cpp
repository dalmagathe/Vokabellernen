#include "guessedword.h"
#include "getnamebackup.h"
#include "ui_guessedword.h"
#include "QSqlQuery"
#include <fstream>
#include <QFileDialog>
#include <QMessageBox>

guessedWord::guessedWord(std::vector<int> idTranslationEntry, std::vector<int> idArticleEntry, std::vector<int> idPluralEntry, QWidget *parent) : QDialog(parent), ui(new Ui::guessedWord)
{
    ui->setupUi(this);

    idTranslation = idTranslationEntry;
    idArticle = idArticleEntry;
    idPlural = idPluralEntry;

    findBDDTranslationMode();
    findBDDArticleMode();
    findBDDPluralMode();
}

guessedWord::~guessedWord()
{
    delete ui;
}

void guessedWord::findBDDTranslationMode()
{
    QSqlQuery query;

    for (int i(0); i < idTranslation.size(); i++)
    {
        query.prepare(QString("SELECT frenchTranslation, englishTranslation, germanTranslation FROM words WHERE idWord=:id"));
        query.bindValue(":id", idTranslation[i]);
        query.exec();
        query.first();

        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(query.value(1).toString()));

        ui->tableWidget->resizeColumnsToContents();
    }
}

void guessedWord::findBDDArticleMode()
{
    QSqlQuery queryNoun;

    for (int i(0); i < idArticle.size(); i++)
    {
        queryNoun.prepare(QString("SELECT article, germanNoun, frenchNoun FROM noun WHERE idNoun=:id"));
        queryNoun.bindValue(":id", idArticle[i]);
        queryNoun.exec();
        queryNoun.first();

        ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
        ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem(queryNoun.value(0).toString()));
        ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem(queryNoun.value(1).toString()));
        ui->tableWidget_2->setItem(i, 2, new QTableWidgetItem(queryNoun.value(2).toString()));

        ui->tableWidget_2->resizeColumnsToContents();
    }
}

void guessedWord::findBDDPluralMode()
{
    QSqlQuery quer;

    ui->tableWidget->setColumnWidth(0, this->width()/3);
    ui->tableWidget->setColumnWidth(1, this->width()/3);
    ui->tableWidget->setColumnWidth(2, this->width()/3);

    for (int i(0); i < idPlural.size(); i++)
    {
        quer.prepare(QString("SELECT nounPlurial, germanNoun, frenchNoun FROM noun WHERE idNoun=:id"));
        quer.bindValue(":id", idPlural[i]);
        quer.exec();
        quer.first();

        ui->tableWidget_3->insertRow(ui->tableWidget_3->rowCount());
        ui->tableWidget_3->setItem(i, 0, new QTableWidgetItem(quer.value(0).toString()));
        ui->tableWidget_3->setItem(i, 1, new QTableWidgetItem(quer.value(1).toString()));
        ui->tableWidget_3->setItem(i, 2, new QTableWidgetItem(quer.value(2).toString()));


    }
}

void guessedWord::resizeEvent(QResizeEvent *)
{
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setColumnWidth(0, ui->tableWidget->width()/3);
    ui->tableWidget->setColumnWidth(1, ui->tableWidget->width()/3);
    ui->tableWidget->setColumnWidth(2, ui->tableWidget->width()/3);

    ui->tableWidget_2->verticalHeader()->setVisible(false);
    ui->tableWidget_2->setColumnWidth(0, ui->tableWidget_2->width()/3);
    ui->tableWidget_2->setColumnWidth(1, ui->tableWidget_2->width()/3);
    ui->tableWidget_2->setColumnWidth(2, ui->tableWidget_2->width()/3);

    ui->tableWidget_3->verticalHeader()->setVisible(false);
    ui->tableWidget_3->setColumnWidth(0, ui->tableWidget_3->width()/3);
    ui->tableWidget_3->setColumnWidth(1, ui->tableWidget_3->width()/3);
    ui->tableWidget_3->setColumnWidth(2, ui->tableWidget_3->width()/3);
}


void guessedWord::on_textEditorBtn_clicked()
{
    QString directory_Name = QFileDialog::getExistingDirectory(this, "Open a directory", "C://");
    getNameBackup *nameBackupFileWindow = new getNameBackup(this);
    nameBackupFileWindow->exec();

    std::ofstream wordsFlux(directory_Name.toStdString() +"/"+ nameBackupFileWindow->get_nameFile().toStdString() + ".txt", std::ios::app);

    if(wordsFlux)
    {
        for(int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            wordsFlux << ui->tableWidget->item(i,0)->text().toStdString() << ";" << ui->tableWidget->item(i,1)->text().toStdString() << ";" << ui->tableWidget->item(i,2)->text().toStdString() <<std::endl;
        }

        for(int i = 0; i < ui->tableWidget_2->rowCount(); i++)
        {
            wordsFlux << ui->tableWidget_2->item(i,0)->text().toStdString() << ";" << ui->tableWidget_2->item(i,1)->text().toStdString() << ";" << ui->tableWidget_2->item(i,2)->text().toStdString() <<std::endl;
        }

        for(int i = 0; i < ui->tableWidget_3->rowCount(); i++)
        {
            wordsFlux << ui->tableWidget_3->item(i,0)->text().toStdString() << ";" << ui->tableWidget_3->item(i,1)->text().toStdString() << ";" << ui->tableWidget_3->item(i,2)->text().toStdString() <<std::endl;
        }

        QMessageBox::information(this, "Backup created", "The backup file with the list of guessed words has been created.");
    }

    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }

}
