#ifndef ANSWER_H
#define ANSWER_H

#include <QDialog>

namespace Ui {
class Answer;
}

class Answer : public QDialog
{
    Q_OBJECT

public:
    explicit Answer(const QString frenchDB, const QString germanDB, const QString englishDB, QWidget *parent = nullptr);
    explicit Answer(const QString frenchDB, const QString germanDB, const QString englishDB, const QString articleDB, const QString pluralDB, QWidget *parent = nullptr);
    ~Answer();

private slots:
    void on_yes_clicked();
    void on_no_clicked();

private:
    Ui::Answer *ui;
    QString frenchDB;
    QString germanDB;
    QString englishDB;
    QString pluralDB;
    QString articleDB;
};

#endif // ANSWER_H
