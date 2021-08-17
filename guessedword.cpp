#include "guessedword.h"
#include "ui_guessedword.h"
#include "QSqlQuery"

guessedWord::guessedWord(std::vector<int> idGuessedWordsEntry, QWidget *parent) : QDialog(parent), ui(new Ui::guessedWord)
{
    ui->setupUi(this);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget_2->resizeColumnsToContents();
    ui->tableWidget_3->resizeColumnsToContents();

    idGuessedWords = idGuessedWordsEntry;

    for (int i(0); i < idGuessedWordsEntry.size(); i++)
    {
        std::cout << idGuessedWords[i] << std::endl;
    }

    findBDD();
}

guessedWord::~guessedWord()
{
    delete ui;
}

void guessedWord::findBDD()
{
    QSqlQuery query;

    for (int i(0); i < idGuessedWords.size(); i++)
    {
        query.prepare(QString("SELECT frenchTranslation, englishTranslation, germanTranslation FROM words WHERE idWord=:id"));
        query.bindValue(":id", idGuessedWords[i]);
        query.exec();
        query.first();

        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(query.value(1).toString()));

        std::cout << query.value(0).toString().toStdString()<< std::endl;
    }

}

