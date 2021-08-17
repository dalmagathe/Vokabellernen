#include "guessedword.h"
#include "ui_guessedword.h"
#include "QSqlQuery"

guessedWord::guessedWord(std::vector<int> idTranslationEntry, std::vector<int> idArticleEntry, std::vector<int> idPluralEntry, QWidget *parent) : QDialog(parent), ui(new Ui::guessedWord)
{
    ui->setupUi(this);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget_2->resizeColumnsToContents();
    ui->tableWidget_3->resizeColumnsToContents();

    idTranslation = idTranslationEntry;
    idArticle = idArticleEntry;
    idPlural = idPluralEntry;

    for (int i(0); i < idTranslationEntry.size(); i++)
    {
        std::cout << idTranslation[i] << std::endl;
    }

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

        ui->tableWidget_2->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem(queryNoun.value(0).toString()));
        ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem(queryNoun.value(1).toString()));
        ui->tableWidget_2->setItem(i, 2, new QTableWidgetItem(queryNoun.value(2).toString()));
    }
}

void guessedWord::findBDDPluralMode()
{
    QSqlQuery query;

    for (int i(0); i < idPlural.size(); i++)
    {
        query.prepare(QString("SELECT nounPlural, germanNoun, frenchNoun FROM noun WHERE idNoun=:id"));
        query.bindValue(":id", idPlural[i]);
        query.exec();
        query.first();

        ui->tableWidget_3->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget_3->setItem(i, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget_3->setItem(i, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget_3->setItem(i, 2, new QTableWidgetItem(query.value(2).toString()));

        std::cout << query.value(0).toString().toStdString()<< std::endl;
    }
}

