#ifndef GETNAMEBACKUPFILE_H
#define GETNAMEBACKUPFILE_H

#include <QDialog>

namespace Ui {
class getNameBackupFile;
}

class getNameBackupFile : public QDialog
{
    Q_OBJECT

public:
    explicit getNameBackupFile(QWidget *parent = nullptr);
    ~getNameBackupFile();
    QString get_nameFile();

private slots:
    void on_okBtn_clicked();

private:
    Ui::getNameBackupFile *ui;
    QString nameFile;
};

#endif // GETNAMEBACKUPFILE_H
