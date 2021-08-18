#ifndef GETNAMEBACKUP_H
#define GETNAMEBACKUP_H

#include <QDialog>

namespace Ui {
class getNameBackup;
}

class getNameBackup : public QDialog
{
    Q_OBJECT

public:
    explicit getNameBackup(QWidget *parent = nullptr);
    ~getNameBackup();
    QString get_nameFile();

private slots:
    void on_pushButton_clicked();

private:
    Ui::getNameBackup *ui;
    QString nameFile;
};

#endif // GETNAMEBACKUP_H
