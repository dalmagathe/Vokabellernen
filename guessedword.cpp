#include "guessedword.h"
#include "ui_guessedword.h"

guessedWord::guessedWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::guessedWord)
{
    ui->setupUi(this);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget_2->resizeColumnsToContents();
    ui->tableWidget_3->resizeColumnsToContents();
}

guessedWord::~guessedWord()
{
    delete ui;
}

