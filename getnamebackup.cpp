#include "getnamebackup.h"
#include "ui_getnamebackup.h"
#include <iostream>
#include <QMessageBox>

getNameBackup::getNameBackup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::getNameBackup)
{
    ui->setupUi(this);
}

getNameBackup::~getNameBackup()
{
    delete ui;
}

void getNameBackup::on_pushButton_clicked()
{
    nameFile = ui->nameFile->text();
    if (nameFile != "")
    {
        this->close();
    }
    else
    {
        QMessageBox::critical(this, "Error message", "You need to enter a name for the backup file.");
    }

}

QString getNameBackup::get_nameFile()
{
    return nameFile;
}

