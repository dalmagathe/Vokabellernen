#include "Headers/addNameBackupfile.h"
#include "ui_addNameBackupFile.h"
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>

addNameBackupFile::addNameBackupFile(QWidget *parent, QString directory_Name) :
    QDialog(parent),
    ui(new Ui::addNameBackupFile)
{
    ui->setupUi(this);
     dir = directory_Name;
}

addNameBackupFile::~addNameBackupFile()
{
    delete ui;
}

void addNameBackupFile::on_pushButton_clicked()
{
    nameFile = ui->nameFile->text();
    if(QDir(dir).exists(nameFile+ ".txt"))
    {
        QMessageBox::warning(this, "ERROR", "The file already exists.");
    }
    else if (nameFile != "")
    {
        this->close();
    }
    else
    {
        QMessageBox::critical(this, "Error message", "You need to enter a name for the backup file.");
        return;
    }
}

QString addNameBackupFile::get_nameFile()
{
    return nameFile;
}

