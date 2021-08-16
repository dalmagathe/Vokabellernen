#ifndef GUESSEDWORD_H
#define GUESSEDWORD_H

#include <QDialog>

namespace Ui {
class guessedWord;
}

class guessedWord : public QDialog
{
    Q_OBJECT

public:
    explicit guessedWord(QWidget *parent = nullptr);
    ~guessedWord();

private:
    Ui::guessedWord *ui;
    int rows;
    int columns;
};

#endif // GUESSEDWORD_H
