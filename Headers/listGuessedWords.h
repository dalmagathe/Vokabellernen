#ifndef LISTlistGuessedWordsS_H
#define LISTlistGuessedWordsS_H

#include <iostream>
#include <QDialog>
#include <vector>

namespace Ui {
class listGuessedWords;
}

class listGuessedWords : public QDialog
{
    Q_OBJECT

public:
    explicit listGuessedWords(std::vector<int> idTranslationEntry, std::vector<int> idArticleEntry, std::vector<int> idPluralEntry, QWidget *parent);
    ~listGuessedWords();

private slots:
    void on_textEditorBtn_clicked();

private:
    Ui::listGuessedWords *ui;
    void findDBTranslationMode();
    void findDBArticleMode();
    void findDBPluralMode();
    void resizeEvent(QResizeEvent *);
    int rows;
    int columns;
    std::vector<int> idTranslation;
    std::vector<int> idArticle;
    std::vector<int> idPlural;
};

#endif // LISTlistGuessedWordsS_H
