#include "guessedword.h"
#include "ui_guessedword.h"
#include "QSqlQuery"

guessedWord::guessedWord(std::vector<int> idTranslationEntry, std::vector<int> idArticleEntry, std::vector<int> idPluralEntry, QWidget *parent) : QDialog(parent), ui(new Ui::guessedWord)
{
    ui->setupUi(this);

    idTranslation = idTranslationEntry;
    idArticle = idArticleEntry;
    idPlural = idPluralEntry;

    for (int i = 0; i < idTranslation.size(); i++)
    {
        std::cout << "id translation after" << idTranslation[i] << std::endl;
    }

    for (int i = 0; i < idArticle.size(); i++)
    {
        std::cout << "id article after" << idArticle[i] << std::endl;
    }

    for (int i = 0; i < idPlural.size(); i++)
    {
        std::cout << "id plural after" << idPlural[i] << std::endl;
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
    std::cout << "In findBDDTranslationMode" << std::endl;
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
    std::cout << "In findBDDArticleMode" << std::endl;
    QSqlQuery queryNoun;

    for (int i(0); i < idArticle.size(); i++)
    {
        queryNoun.prepare(QString("SELECT article, germanNoun, frenchNoun FROM noun WHERE idNoun=:id"));
        queryNoun.bindValue(":id", idArticle[i]);
        queryNoun.exec();
        queryNoun.first();

        std::cout << queryNoun.value(0).toString().toStdString() << std::endl;
        ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
        ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem(queryNoun.value(0).toString()));
        ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem(queryNoun.value(1).toString()));
        ui->tableWidget_2->setItem(i, 2, new QTableWidgetItem(queryNoun.value(2).toString()));

        ui->tableWidget_2->resizeColumnsToContents();
    }
}

void guessedWord::findBDDPluralMode()
{
    std::cout << "In findBDDPluralMode" << std::endl;
    QSqlQuery quer;

    for (int i(0); i < idPlural.size(); i++)
    {
        std::cout << idPlural[i] << std::endl;
        quer.prepare(QString("SELECT nounPlurial, germanNoun, frenchNoun FROM noun WHERE idNoun=:id"));
        quer.bindValue(":id", idPlural[i]);
        quer.exec();
        quer.first();
        std::cout << quer.value(0).toString().toStdString() << std::endl;
        std::cout << quer.value(1).toString().toStdString() << std::endl;
        std::cout << quer.value(2).toString().toStdString() << std::endl;

        ui->tableWidget_3->insertRow(ui->tableWidget_3->rowCount());
        ui->tableWidget_3->setItem(i, 0, new QTableWidgetItem(quer.value(0).toString()));
        ui->tableWidget_3->setItem(i, 1, new QTableWidgetItem(quer.value(1).toString()));
        ui->tableWidget_3->setItem(i, 2, new QTableWidgetItem(quer.value(2).toString()));

        ui->tableWidget_3->resizeColumnsToContents();

    }
}

