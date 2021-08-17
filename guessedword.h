#ifndef GUESSEDWORD_H
#define GUESSEDWORD_H

#include <iostream>
#include <QDialog>
#include <vector>

namespace Ui {
class guessedWord;
}

class guessedWord : public QDialog
{
    Q_OBJECT

public:
    explicit guessedWord(std::vector<int> idGuessedWordsEntry, QWidget *parent);
    ~guessedWord();
    void findBDD();

private:
    Ui::guessedWord *ui;
    int rows;
    int columns;
    std::vector<int> idGuessedWords;
    //firstColumn = german, article, germanPluralForm
    //QString firstColumn;
    //secondColumn = french, german, germanSingularForm
    //QString secondColumn;
    //thirdColun = english, french, frenchSingularForm
    //QString thirdColumn;
};

#endif // GUESSEDWORD_H
