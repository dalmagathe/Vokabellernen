#include "namebackupfile.h"
#include "ui_namebackupfile.h"
#include "iostream"

nameBackupFile::nameBackupFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nameBackupFile)
{
    //ui->setupUi(this);
}

nameBackupFile::~nameBackupFile()
{
    delete ui;
}

void nameBackupFile::on_pushButton_clicked()
{
    nameFile = ui->nameFile->text();
    std::cout << "test avant" << nameFile.toStdString() << std::endl;
}

QString nameBackupFile::get_nameFile()
{
    return nameFile;
}
