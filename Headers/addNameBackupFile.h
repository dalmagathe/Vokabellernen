#ifndef ADDNAMEBACKUPFILE_H
#define ADDNAMEBACKUPFILE_H

#include <QDialog>

namespace Ui {
class addNameBackupFile;
}

class addNameBackupFile : public QDialog
{
    Q_OBJECT

public:
    explicit addNameBackupFile(QWidget *parent = nullptr, QString directory_Name = "");
    ~addNameBackupFile();
    QString get_nameFile();

private slots:
    void on_pushButton_clicked();

private:
    Ui::addNameBackupFile *ui;
    QString dir;
    QString nameFile;
};

#endif // ADDNAMEBACKUPFILE_H
