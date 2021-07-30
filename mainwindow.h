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
    void on_pushButton_2_clicked();
    void on_btnAdd_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_pushButton_clicked();
    void on_btnGenerate_clicked();
    void on_checkArticleTranslation_clicked();
    void on_menuArtcileTranslation_clicked();
    void on_generateNoun_clicked();
    void on_menuPluralBtn_clicked();
    void on_generatePluralBtn_clicked();
    void on_checkGeneralBtn_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase database;

    QString wordList [6];
    void clearList();
    int french;
    int german;
    QString frenchTranslationUI;
    QString englishTranslationUI;
    QString germanTranslationUI;
    QString frenchTranslation;
    QString englishTranslation;
    QString germanTranslation;
    QString articleTranslation;
    QString germanNounTranslation;
    QString nounPlurialTranslation;
    QString frenchNounTranslation;
    QString englishNounTranslation;
    QString articleTranslationUI;
    QString germanNounTranslationUI;
    QString nounPlurialTranslationUI;
    QString frenchNounTranslationUI;
    QString englishNounTranslationUI;
    QString pluralTranslation;
    QString germanPluralTranslation;
    QString frenchPluralTranslation;
    QString pluralTranslationUI;
    QString germanPluralTranslationUI;
    QString frenchPluralTranslationUI;

};

enum wordIdList {id, german, english, french, article, plural};
#endif // MAINWINDOW_H
