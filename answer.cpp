#include "Headers/answer.h"
#include "ui_answer.h"
#include "iostream"

Answer::Answer(const QString frenchDB, QString germanDB, QString englishDB, QWidget *parent) : QDialog(parent), ui(new Ui::Answer), frenchDB(frenchDB), germanDB(germanDB), englishDB(englishDB)
{
    ui->setupUi(this);
}

Answer::Answer(const QString frenchDB, const QString germanDB, const QString englishDB, const QString articleDB, const QString pluralDB, QWidget *parent) : QDialog(parent), ui(new Ui::Answer), frenchDB(frenchDB), germanDB(germanDB), englishDB(englishDB), pluralDB(pluralDB), articleDB(articleDB)
{
    ui->setupUi(this);
}

Answer::~Answer()
{
    delete ui;
}

void Answer::on_yes_clicked()
{
    this->resize(540, 180);

    ui->stackedWidget->setCurrentIndex(1);
    ui->frenchDB->setText(frenchDB);
    ui->germanDB->setText(germanDB);
    ui->englishDB->setText(englishDB);
    ui->articleDB->setText(articleDB);
    ui->pluraDB->setText(pluralDB);

    ui->frenchDB->setReadOnly(1);
    ui->germanDB->setReadOnly(1);
    ui->englishDB->setReadOnly(1);
    ui->articleDB->setReadOnly(1);
    ui->pluraDB->setReadOnly(1);
}

void Answer::on_no_clicked()
{
    this->close();
}
