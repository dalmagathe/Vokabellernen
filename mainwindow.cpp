#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlQuery"
#include "iostream"
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), wordList{"", "", "", "", "", ""}
{
    ui->setupUi(this);

    remove("D:/words.txt");

    //Connection to the database
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost"); //localhost:3307
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("vocabularyproject");

    //Alow to add the article in case the user want to add a noun
    ui->groupBoxArticle->setCheckable(true);
    ui->groupBoxArticle->setChecked(false);
    ui->statusbar->showMessage("");
    ui->statusbar->addPermanentWidget(ui->labelStatusBar, 1);
    ui->labelStatusBar->setText("");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAddWord_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->labelStatusBar->setText("On the feature add word");
}

void MainWindow::on_btnWordWindow_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->labelStatusBar->setText("On the feature to guess a word");
}

void MainWindow::on_btnReturAdd_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->labelStatusBar->setText("");
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->labelStatusBar->setText("");
}

void MainWindow::on_btnArticleWindow_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->labelStatusBar->setText("On the feature to guess the article of a noun");
}

void MainWindow::on_btnVerbWindow_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->labelStatusBar->setText("On the feature to guess the plural form of a noun");
}

void MainWindow::on_menuArtcileTranslation_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->labelStatusBar->setText("");
}

void MainWindow::on_menuPluralBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->labelStatusBar->setText("");
}

void MainWindow::on_btnAdd_clicked()
{
    if(database.open())
    {
        QMessageBox::information(this, "Data problem", "DAtaBAs ouvert");

        //Convert the text in the lines edit to a string

        wordList[wordIdList::german] = ui->addGermanWord->text();
        wordList[wordIdList::english] = ui->addEnglishWord->text();
        wordList[wordIdList::french] = ui->addFrenchWord->text();
        wordList[wordIdList::plural] = ui->addPluralForm->text();

        //Allow to manage data from SQL
        QSqlQuery qryWordNounInsert(database);
        QSqlQuery qryNounInsert(database);
        QSqlQuery qryWordInsert(database);
        QSqlQuery qryCheckWordDB(database);

        qryCheckWordDB.prepare("SELECT idWord FROM words WHERE germanTranslation = :data");
        qryCheckWordDB.bindValue(":data", wordList[wordIdList::german]);
        qryCheckWordDB.exec();
        qryCheckWordDB.first();

        int idWordToAdd = qryCheckWordDB.value(0).toInt();

        //Message to indicate if the data has been inserted
        if(idWordToAdd != 0)
        {
            QMessageBox::information(this, "Inserted", "Word already inserted");

        }

        //If the word to add is a noun the user nedd to add the article
        if (ui->groupBoxArticle->isChecked() && idWordToAdd == 0)
        {
            wordList[wordIdList::article] = ui->addArticle->text();
            wordList[wordIdList::plural] =  ui->addPluralForm->text();

            //Check if the user enter all words.
            if (wordList[wordIdList::english] == "")
            {
                QMessageBox::information(this, "Data problem", "You need to insert the english word.");
            }
            else if (wordList[wordIdList::french] == "")
            {
                QMessageBox::information(this, "Data problem", "You need to insert the french word.");
            }
            else if (wordList[wordIdList::german] == "")
            {
                QMessageBox::information(this, "Data problem", "You need to insert the german word.");
            }
            else if (wordList[wordIdList::article] == "")
            {
                QMessageBox::information(this, "Data problem", "You need to insert the article.");
            }
            else
            {
                qryWordNounInsert.prepare(QString("INSERT INTO words (frenchTranslation, englishTranslation, germanTranslation, articleNoun) VALUES (:addFrenchWord, :addEnglishWord, :addGermanWord, :addArticle)"));
                qryWordNounInsert.bindValue(":addFrenchWord", wordList[wordIdList::french]);
                qryWordNounInsert.bindValue(":addEnglishWord", wordList[wordIdList::english]);
                qryWordNounInsert.bindValue(":addGermanWord", wordList[wordIdList::german]);
                qryWordNounInsert.bindValue(":addArticle", wordList[wordIdList::article]);

                qryNounInsert.prepare(QString("INSERT INTO noun (frenchNoun, englishNoun, article, germanNoun, nounPlurial) VALUES (:addFrenchWord, :addEnglishWord, :addArticle, :addGermanWord, :addPluralForm)"));
                qryNounInsert.bindValue(":addFrenchWord", wordList[wordIdList::french]);
                qryNounInsert.bindValue(":addEnglishWord", wordList[wordIdList::english]);
                qryNounInsert.bindValue(":addGermanWord", wordList[wordIdList::german]);
                qryNounInsert.bindValue(":addArticle", wordList[wordIdList::article]);
                qryNounInsert.bindValue(":addPluralForm", wordList[wordIdList::plural]);

                if(qryWordNounInsert.exec() && qryNounInsert.exec())
                {
                    QMessageBox::information(this, "Inserted", "Noun inserted");

                }
                else
                {
                    QMessageBox::information(this, "Not inserted", "Noun not inserted");
                }
            }
        }
        //If the word to add is not a noun
        else if(idWordToAdd == 0)
        {
            //Check if the user enter all words.
            if (wordList[wordIdList::english] == "")
            {
                QMessageBox::information(this, "Data problem", "You need to insert the english word.");
            }
            else if (wordList[wordIdList::french] == "")
            {
                QMessageBox::information(this, "Data problem", "You need to insert the french word.");
            }
            else if (wordList[wordIdList::german] == "")
            {
                QMessageBox::information(this, "Data problem", "You need to insert the german word.");
            }
            else
            {
                qryWordInsert.prepare(QString("INSERT INTO words (frenchTranslation, englishTranslation, germanTranslation) VALUES (:addFrenchWord, :addEnglishWord, :addGermanWord)"));
                qryWordInsert.bindValue(":addFrenchWord", wordList[wordIdList::french]);
                qryWordInsert.bindValue(":addEnglishWord", wordList[wordIdList::english]);
                qryWordInsert.bindValue(":addGermanWord", wordList[wordIdList::german]);

                //Message to indicate if the data has been inserted
                if(qryWordInsert.exec())
                {
                    QMessageBox::information(this, "Inserted", "Word inserted");
                    clearList();

                }
                else
                {
                    QMessageBox::information(this, "Not inserted", "Word not inserted");
                }
            }

        }
    }
    else
    {
        QMessageBox::information(this, "Not Connection", "Not Success");
    }
    database.close();

}

void MainWindow::clearList()
{
    for (int i (0); i < 6; i++)
    {
        wordList[i] = "";
    }
}

//Allow to indicate if the user want to translate in french/english or in german
void MainWindow::on_radioButton_clicked()
{
    french = 0;
    german = 1;
}

void MainWindow::on_radioButton_2_clicked()
{
    french = 1;
    german = 0;
}

void MainWindow::on_btnGenerate_clicked()
{
    if(database.open())
    {
        QSqlQuery q;
        q.prepare("SELECT COUNT(*) FROM words");
        q.exec();

        int rows= 0;
        while (q.next())
        {
            rows = q.value(0).toInt();
        }

        if(german == 1)
        {
            srand(time(0));

            int position = rand() % rows;

            QSqlQuery query;

            query.prepare(QString("SELECT frenchTranslation, englishTranslation, germanTranslation FROM words WHERE idWord=:id"));
            query.bindValue(":id", position);
            query.exec();
            query.first();

            frenchTranslation = query.value(0).toString();
            englishTranslation = query.value(1).toString();
            germanTranslation = query.value(2).toString();

            ui->checkGerman->setText(germanTranslation);

        }
        else if(french == 1)
        {
            srand(time(0));

            int position = rand() % rows;

            QSqlQuery query;

            query.prepare(QString("SELECT frenchTranslation, englishTranslation, germanTranslation FROM words WHERE idWord=:id"));
            query.bindValue(":id", position);
            query.exec();
            query.first();

            frenchTranslation = query.value(0).toString();
            englishTranslation = query.value(1).toString();
            germanTranslation = query.value(2).toString();

            ui->checkFrench->setText(frenchTranslation);
        }

    }
}

void MainWindow::on_pushButton_clicked()
{
    //Allow to save what the user has written
    frenchTranslationUI = ui->checkFrench->text();
    englishTranslationUI = ui->checkEnglish->text();
    germanTranslationUI = ui->checkGerman->text();

    if(german == 1)
    {
        if(frenchTranslationUI == frenchTranslation && englishTranslationUI == englishTranslation)
        {
            QMessageBox::information(this, "Result", "Good job ! ");
            ui->checkFrench->clear();
            ui->checkEnglish->clear();
            ui->checkGerman->clear();
            fichier(germanTranslationUI);
        }
        else
        {
            QMessageBox::information(this, "Result", "Try again ! ");
        }
    }
    else if(french == 1)
    {
        if(germanTranslationUI == germanTranslation && englishTranslationUI == englishTranslation)
        {
            QMessageBox::information(this, "Result", "Good job ! ");
            ui->checkFrench->clear();
            ui->checkEnglish->clear();
            ui->checkGerman->clear();
            fichier(germanTranslationUI);
        }
        else
        {
            QMessageBox::information(this, "Result", "Try again ! ");
        }
    }

}

void MainWindow::on_generateNoun_clicked()
{
    if(database.open())
    {
        QSqlQuery qNoun;
        qNoun.prepare("SELECT COUNT(*) FROM noun");
        qNoun.exec();

        int rows= 0;
        while (qNoun.next())
        {
            rows = qNoun.value(0).toInt();
        }

        srand(time(0));
        int positionNoun = rand() % rows;

        QSqlQuery queryNoun;

        queryNoun.prepare(QString("SELECT article, germanNoun, frenchNoun FROM noun WHERE idNoun=:id"));
        queryNoun.bindValue(":id", positionNoun);
        queryNoun.exec();
        queryNoun.first();

        articleTranslation = queryNoun.value(0).toString();
        germanNounTranslation = queryNoun.value(1).toString();
        frenchNounTranslation = queryNoun.value(2).toString();


        ui->nounTranslation->setText(germanNounTranslation);
     }
}

void MainWindow::on_checkArticleTranslation_clicked()
{
    //Allow to save what the user has written
    articleTranslationUI = ui->articleTranslation->text();
    frenchNounTranslationUI = ui->frenchArticleTranslation->text();

    if(articleTranslationUI == articleTranslation && frenchNounTranslationUI == frenchNounTranslation)
    {
        QMessageBox::information(this, "Result", "Correct translation");
        ui->articleTranslation->clear();
        ui->frenchArticleTranslation->clear();
        fichier(germanNounTranslation);
    }
    else
    {
        QMessageBox::information(this, "Result", "Fail");
    }
}

void MainWindow::on_generatePluralBtn_clicked()
{
    if(database.open())
    {
        QSqlQuery qPlural;
        qPlural.prepare("SELECT COUNT(*) FROM noun");
        qPlural.exec();

        int rows= 0;
        while (qPlural.next())
        {
            rows = qPlural.value(0).toInt();
        }

        std::cout << rows << std::endl;

        srand(time(0));
        int positionPlural = rand() % rows;

        QSqlQuery queryNoun;

        queryNoun.prepare(QString("SELECT nounPlurial, germanNoun, frenchNoun FROM noun WHERE idNoun=:id"));
        queryNoun.bindValue(":id", positionPlural);
        queryNoun.exec();
        queryNoun.first();

        pluralTranslation = queryNoun.value(0).toString();
        germanPluralTranslation = queryNoun.value(1).toString();
        frenchPluralTranslation = queryNoun.value(2).toString();


        ui->germanPluralForm->setText(germanPluralTranslation);
     }
}

void MainWindow::on_checkGeneralBtn_clicked()
{
    //Allow to save what the user has written
    pluralTranslationUI = ui->pluralForm->text();
    frenchPluralTranslationUI = ui->frenchPluralForm->text();

    if(pluralTranslationUI == pluralTranslation && frenchPluralTranslationUI == frenchPluralTranslation)
    {
        QMessageBox::information(this, "Result", "Correct translation");
        ui->pluralForm->clear();
        ui->frenchPluralForm->clear();
    }
    else
    {
        QMessageBox::information(this, "Result", "Fail");
    }
}

int MainWindow::fichier(QString germanWord)
{
    std::string const words("D:/words.txt");
    std::ofstream wordsFlux(words.c_str(), std::ios::app);

    if(wordsFlux)
    {
        //wordsFlux.seekp(0, std::ios::end);
        wordsFlux << germanWord.toStdString() << "," << std::endl;
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }

    return 0;
}

