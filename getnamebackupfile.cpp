#include "getnamebackupfile.h"
#include "ui_getnamebackupfile.h"
#include <iostream>

getNameBackupFile::getNameBackupFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::getNameBackupFile)
{
    ui->setupUi(this);
}

getNameBackupFile::~getNameBackupFile()
{
    delete ui;
}


QString getNameBackupFile::get_nameFile()
{
    return nameFile;
}

void getNameBackupFile::on_okBtn_clicked()
{
    nameFile = ui->lineEdit->text();
    std::cout << "test avant" << nameFile.toStdString() << std::endl;
}
