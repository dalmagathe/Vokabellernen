#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <string>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int fichier(QString germanWord);

private slots:
    void on_btnAddWord_clicked();
    void on_btnWordWindow_clicked();
    void on_btnArticleWindow_clicked();
    void on_btnVerbWindow_clicked();
    void on_btnReturAdd_clicked();
    void on_btnMenuTranslate_clicked();
    void on_btnAdd_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();

    void on_btnCheckTranslate_clicked();
    void on_btnGenerateTranslate_clicked();

    void on_btnCheckArticle_clicked();
    void on_btnMenuArticle_clicked();
    void on_btnGenerateNounArticle_clicked();

    void on_btnMenuPlural_clicked();
    void on_btnGenerateNounPlural_clicked();
    void on_btnCheckPlural_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase database;

    QString wordList [11];
    void clearList();
    int french;
    int german;

};

enum wordIdList {id, germanBDD, germanUSER, englishBDD, englishUSER, frenchBDD, frenchUSER, articleBDD, articleUSER, pluralBDD, pluralUSER};
#endif // MAINWINDOW_H
