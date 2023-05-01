#include "Headers/listGuessedWords.h"
#include "Headers/addNameBackupFile.h"
#include "ui_listGuessedWords.h"
#include "QSqlQuery"
#include <fstream>
#include <QFileDialog>
#include <QMessageBox>

listGuessedWords::listGuessedWords(std::vector<int> idTranslationEntry, std::vector<int> idArticleEntry, std::vector<int> idPluralEntry, QWidget *parent) : QDialog(parent), ui(new Ui::listGuessedWords)
{
    ui->setupUi(this);

    idTranslation = idTranslationEntry;
    idArticle = idArticleEntry;
    idPlural = idPluralEntry;

    findDBTranslationMode();
    findDBArticleMode();
    findDBPluralMode();
}

listGuessedWords::~listGuessedWords()
{
    delete ui;
}

void listGuessedWords::findDBTranslationMode()
{
    QSqlQuery query;

    for (uint i(0); i < idTranslation.size(); i++)
    {
        query.prepare(QString("SELECT frenchTranslation, englishTranslation, germanTranslation FROM words WHERE idWord=:id"));
        query.bindValue(":id", idTranslation[i]);
        query.exec();
        query.first();

        ui->table_Translation->insertRow(ui->table_Translation->rowCount());
        ui->table_Translation->setItem(i, 0, new QTableWidgetItem(query.value(2).toString()));
        ui->table_Translation->setItem(i, 1, new QTableWidgetItem(query.value(0).toString()));
        ui->table_Translation->setItem(i, 2, new QTableWidgetItem(query.value(1).toString()));

        ui->table_Translation->resizeColumnsToContents();
    }
}

void listGuessedWords::findDBArticleMode()
{
    QSqlQuery queryNoun;

    for (uint i(0); i < idArticle.size(); i++)
    {
        queryNoun.prepare(QString("SELECT article, germanNoun, frenchNoun FROM noun WHERE idNoun=:id"));
        queryNoun.bindValue(":id", idArticle[i]);
        queryNoun.exec();
        queryNoun.first();

        ui->table_Article->insertRow(ui->table_Article->rowCount());
        ui->table_Article->setItem(i, 0, new QTableWidgetItem(queryNoun.value(0).toString()));
        ui->table_Article->setItem(i, 1, new QTableWidgetItem(queryNoun.value(1).toString()));
        ui->table_Article->setItem(i, 2, new QTableWidgetItem(queryNoun.value(2).toString()));

        ui->table_Article->resizeColumnsToContents();
    }
}

void listGuessedWords::findDBPluralMode()
{
    QSqlQuery quer;

    ui->table_Translation->setColumnWidth(0, this->width()/3);
    ui->table_Translation->setColumnWidth(1, this->width()/3);
    ui->table_Translation->setColumnWidth(2, this->width()/3);

    for (uint i(0); i < idPlural.size(); i++)
    {
        quer.prepare(QString("SELECT nounPlurial, germanNoun, frenchNoun FROM noun WHERE idNoun=:id"));
        quer.bindValue(":id", idPlural[i]);
        quer.exec();
        quer.first();

        ui->table_Plural->insertRow(ui->table_Plural->rowCount());
        ui->table_Plural->setItem(i, 0, new QTableWidgetItem(quer.value(0).toString()));
        ui->table_Plural->setItem(i, 1, new QTableWidgetItem(quer.value(1).toString()));
        ui->table_Plural->setItem(i, 2, new QTableWidgetItem(quer.value(2).toString()));


    }
}

void listGuessedWords::resizeEvent(QResizeEvent *)
{
    ui->table_Translation->verticalHeader()->setVisible(false);
    ui->table_Translation->setColumnWidth(0, ui->table_Translation->width()/3);
    ui->table_Translation->setColumnWidth(1, ui->table_Translation->width()/3);
    ui->table_Translation->setColumnWidth(2, ui->table_Translation->width()/3);

    ui->table_Article->verticalHeader()->setVisible(false);
    ui->table_Article->setColumnWidth(0, ui->table_Article->width()/3);
    ui->table_Article->setColumnWidth(1, ui->table_Article->width()/3);
    ui->table_Article->setColumnWidth(2, ui->table_Article->width()/3);

    ui->table_Plural->verticalHeader()->setVisible(false);
    ui->table_Plural->setColumnWidth(0, ui->table_Plural->width()/3);
    ui->table_Plural->setColumnWidth(1, ui->table_Plural->width()/3);
    ui->table_Plural->setColumnWidth(2, ui->table_Plural->width()/3);
}


void listGuessedWords::on_textEditorBtn_clicked()
{
    //Check if words have been guessed
    if(!(ui->table_Translation->rowCount() != 0 || ui->table_Article->rowCount() != 0 || ui->table_Plural->rowCount() != 0))
    {
        QMessageBox::information(this, "Impossible", "No words were guessed. The backup file is therefore not created.");
        return;
    }

    QString directory_Name = QFileDialog::getExistingDirectory(this, "Open a directory", "C://");

    //Check if the user has chosen a path to save the file
    if (!(directory_Name != ""))
    {
        QMessageBox::critical(this, "ERROR", "Please, choose a folder to save the backup file.");
        return;
    }

    //Run the window allowing to choose the file's name
    addNameBackupFile *nameBackupFileWindow = new addNameBackupFile(this, directory_Name);
    nameBackupFileWindow->exec();

    //Event in case the second window is closed by the exit button
    if(nameBackupFileWindow->get_nameFile() == ""){
        return;
    }

    //Create and write in the file
    std::ofstream wordsFlux(directory_Name.toStdString() +"/"+ nameBackupFileWindow->get_nameFile().toStdString() + ".txt", std::ios::app);
    if(wordsFlux)
    {
        for(int i = 0; i < ui->table_Translation->rowCount(); i++)
        {
            wordsFlux << ui->table_Translation->item(i,0)->text().toStdString() << ";" << ui->table_Translation->item(i,1)->text().toStdString() << ";" << ui->table_Translation->item(i,2)->text().toStdString() <<std::endl;
        }

        for(int i = 0; i < ui->table_Article->rowCount(); i++)
        {
            wordsFlux << ui->table_Article->item(i,0)->text().toStdString() << ";" << ui->table_Article->item(i,1)->text().toStdString() << ";" << ui->table_Article->item(i,2)->text().toStdString() <<std::endl;
        }

        for(int i = 0; i < ui->table_Plural->rowCount(); i++)
        {
            wordsFlux << ui->table_Plural->item(i,0)->text().toStdString() << ";" << ui->table_Plural->item(i,1)->text().toStdString() << ";" << ui->table_Plural->item(i,2)->text().toStdString() <<std::endl;
        }

        QMessageBox::information(this, "Backup created", "The backup file with the list of guessed words has been created.");
    }

    else
    {
        QMessageBox::warning(this, "ERROR", "The file has not been created.");
    }
}
