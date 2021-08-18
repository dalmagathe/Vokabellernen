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
    explicit guessedWord(std::vector<int> idTranslationEntry, std::vector<int> idArticleEntry, std::vector<int> idPluralEntry, QWidget *parent);
    ~guessedWord();

private:
    Ui::guessedWord *ui;
    void findBDDTranslationMode();
    void findBDDArticleMode();
    void findBDDPluralMode();
    void resizeEvent(QResizeEvent *);
    int rows;
    int columns;
    std::vector<int> idTranslation;
    std::vector<int> idArticle;
    std::vector<int> idPlural;
    //firstColumn = german, article, germanPluralForm
    //QString firstColumn;
    //secondColumn = french, german, germanSingularForm
    //QString secondColumn;
    //thirdColun = english, french, frenchSingularForm
    //QString thirdColumn;
};

#endif // GUESSEDWORD_H
