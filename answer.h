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
    //explicit Answer(const QString code [11], QWidget *parent = nullptr);
    explicit Answer(const QString frenchBDD, const QString germanBDD, const QString englishBDD, QWidget *parent = nullptr);
    explicit Answer(const QString frenchBDD, const QString germanBDD, const QString englishBDD, const QString articleBDD, const QString pluralBDD, QWidget *parent = nullptr);
    ~Answer();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Answer *ui;
    QString frenchBDD;
    QString germanBDD;
    QString englishBDD;
    QString pluralBDD;
    QString articleBDD;
};

#endif // ANSWER_H
