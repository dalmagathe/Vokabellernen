#ifndef NAMEBACKUPFILE_H
#define NAMEBACKUPFILE_H

#include <QMainWindow>
#include <string>

namespace Ui {
class nameBackupFile;
}

class nameBackupFile : public QMainWindow
{
    Q_OBJECT

public:
    explicit nameBackupFile(QWidget *parent = nullptr);
    ~nameBackupFile();
    QString get_nameFile();
    int trigger;

private slots:
    void on_pushButton_clicked();

private:
    Ui::nameBackupFile *ui;
    QString nameFile;
};

#endif // NAMEBACKUPFILE_H
