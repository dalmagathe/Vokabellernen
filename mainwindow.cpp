#include "Headers/mainwindow.h"
#include "Headers/answer.h"
#include "ui_mainWindow.h"
#include "QSqlQuery"
#include "iostream"
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <QVBoxLayout>
#include <Headers/listGuessedWords.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), wordList{"", "", "", "", "", "", "", "", "", "", ""}, position(0), positionNoun(0), positionPlural(0)
{
    ui->setupUi(this);

    this->setFixedSize(QSize(953, 385));

    remove("D:/words.txt");

    //Connection to the database
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost"); //localhost:3307
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("vocabularyproject");

    //Alow to add the article in case the user want to add a noun
    ui->groupNoun->setCheckable(true);
    ui->groupNoun->setChecked(false);
    ui->statusbar->showMessage("");
    ui->statusbar->addPermanentWidget(ui->labelStatusBar, 1);
    ui->labelStatusBar->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openDB()
{
    if(database.open())
    {
        ui->btnAddWord->setEnabled(1);
        ui->btnArticleWindow->setEnabled(1);
        ui->btnVerbWindow->setEnabled(1);
        ui->btnWordWindow->setEnabled(1);
        QMessageBox::information(this, "Status of the DB", "Database is opened.");
    }
    else
    {
        ui->btnAddWord->setEnabled(0);
        ui->btnArticleWindow->setEnabled(0);
        ui->btnVerbWindow->setEnabled(0);
        ui->btnWordWindow->setEnabled(0);
        QMessageBox::information(this, "Status of the DB", "Database is not opened.");
    }
}

//**************MENU PAGE**************//
void MainWindow::on_btnAddWord_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->labelStatusBar->setText("On the feature \"Adding words\"");
}

void MainWindow::on_btnArticleWindow_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->labelStatusBar->setText("On the feature \"Guessing article before a noun\"");
}

void MainWindow::on_btnVerbWindow_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->labelStatusBar->setText("On the feature \"Guess plural form of a noun\"");
}

void MainWindow::on_btnWordWindow_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->labelStatusBar->setText("On the feature \"Guessing words\"");
}


//**************ADD WORD PAGE**************//
void MainWindow::on_btnReturAdd_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->labelStatusBar->setText("");
}

void MainWindow::on_btnAdd_clicked()
{
    wordList[wordIdList::germanUSER] = ui->addGermanWord->text();
    wordList[wordIdList::englishUSER] = ui->addEnglishWord->text();
    wordList[wordIdList::frenchUSER] = ui->addFrenchWord->text();
    wordList[wordIdList::pluralUSER] = ui->addPluralForm->text();

    inputDataFormatting();

    //Allow to manage data from SQL
    QSqlQuery qryWordNounInsert(database);
    QSqlQuery qryNounInsert(database);
    QSqlQuery qryWordInsert(database);
    QSqlQuery qryCheckWordDB(database);

    qryCheckWordDB.prepare("SELECT idWord FROM words WHERE germanTranslation = :data");
    qryCheckWordDB.bindValue(":data", wordList[wordIdList::germanUSER]);
    qryCheckWordDB.exec();
    qryCheckWordDB.first();

    int idWordToAdd = qryCheckWordDB.value(0).toInt();

    //Message to indicate if the data has been inserted
    if(idWordToAdd != 0)
    {
        QMessageBox::information(this, "Inserted", "Word already inserted");
    }

    //If the word to add is a noun the user nedd to add the article
    if (ui->groupNoun->isChecked() && idWordToAdd == 0)
    {
        wordList[wordIdList::articleUSER] = ui->addArticle->text();
        wordList[wordIdList::pluralUSER] =  ui->addPluralForm->text();

        wordList[wordIdList::articleUSER] = wordList[wordIdList::articleUSER].toLower();
        wordList[wordIdList::articleUSER][0] = wordList[wordIdList::articleUSER][0].toUpper();
        wordList[wordIdList::pluralUSER] = wordList[wordIdList::pluralUSER].toLower();
        wordList[wordIdList::pluralUSER][0] = wordList[wordIdList::pluralUSER][0].toUpper();

        //Check if the user enter all words.
        if (wordList[wordIdList::englishUSER] == "")
        {
            QMessageBox::information(this, "Data problem", "You need to insert the english word.");
        }
        else if (wordList[wordIdList::frenchUSER] == "")
        {
            QMessageBox::information(this, "Data problem", "You need to insert the french word.");
        }
        else if (wordList[wordIdList::germanUSER] == "")
        {
            QMessageBox::information(this, "Data problem", "You need to insert the german word.");
        }
        else if (wordList[wordIdList::articleUSER] == "")
        {
            QMessageBox::information(this, "Data problem", "You need to insert the article.");
        }
        else
        {
            qryWordNounInsert.prepare(QString("INSERT INTO words (frenchTranslation, englishTranslation, germanTranslation, articleNoun) VALUES (:addFrenchWord, :addEnglishWord, :addGermanWord, :addArticle)"));
            qryWordNounInsert.bindValue(":addFrenchWord", wordList[wordIdList::frenchUSER]);
            qryWordNounInsert.bindValue(":addEnglishWord", wordList[wordIdList::englishUSER]);
            qryWordNounInsert.bindValue(":addGermanWord", wordList[wordIdList::germanUSER]);
            qryWordNounInsert.bindValue(":addArticle", wordList[wordIdList::articleUSER]);

            qryNounInsert.prepare(QString("INSERT INTO noun (frenchNoun, englishNoun, article, germanNoun, nounPlurial) VALUES (:addFrenchWord, :addEnglishWord, :addArticle, :addGermanWord, :addPluralForm)"));
            qryNounInsert.bindValue(":addFrenchWord", wordList[wordIdList::frenchUSER]);
            qryNounInsert.bindValue(":addEnglishWord", wordList[wordIdList::englishUSER]);
            qryNounInsert.bindValue(":addGermanWord", wordList[wordIdList::germanUSER]);
            qryNounInsert.bindValue(":addArticle", wordList[wordIdList::articleUSER]);
            qryNounInsert.bindValue(":addPluralForm", wordList[wordIdList::pluralUSER]);

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
        if (wordList[wordIdList::englishUSER] == "")
        {
            QMessageBox::information(this, "Data problem", "You need to insert the english word.");
        }
        else if (wordList[wordIdList::frenchUSER] == "")
        {
            QMessageBox::information(this, "Data problem", "You need to insert the french word.");
        }
        else if (wordList[wordIdList::germanUSER] == "")
        {
            QMessageBox::information(this, "Data problem", "You need to insert the german word.");
        }
        else
        {
            qryWordInsert.prepare(QString("INSERT INTO words (frenchTranslation, englishTranslation, germanTranslation) VALUES (:addFrenchWord, :addEnglishWord, :addGermanWord)"));
            qryWordInsert.bindValue(":addFrenchWord", wordList[wordIdList::frenchUSER]);
            qryWordInsert.bindValue(":addEnglishWord", wordList[wordIdList::englishUSER]);
            qryWordInsert.bindValue(":addGermanWord", wordList[wordIdList::germanUSER]);

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



//**************GUESS TRANSLATION PAGE**************//
//Allow to indicate if the user want to translate in french/english or in german
void MainWindow::on_radioBtnGuessFromG_clicked()
{
    frenchEnglish = 0;
    german = 1;
}

void MainWindow::on_radioBtnGuessFromEF_clicked()
{
    frenchEnglish = 1;
    german = 0;
}

void MainWindow::on_btnGenerateTranslate_clicked()
{
    QSqlQuery q;
    q.prepare("SELECT COUNT(*) FROM words");
    q.exec();
    int rows = 0;

    while (q.next())
    {
        rows = q.value(0).toInt();
    }

    if(rows == 0){
        QMessageBox::warning(this, "Database empty", "The database is empty. You must first insert words.");
    }
    else{
        if(german == 1)
        {
            srand(time(0));
            position = rand() % rows;

            QSqlQuery query;

            query.prepare(QString("SELECT frenchTranslation, englishTranslation, germanTranslation FROM words WHERE idWord=:id"));
            query.bindValue(":id", position);
            query.exec();
            query.first();

            wordList[wordIdList::frenchDB] = query.value(0).toString();
            wordList[wordIdList::englishDB] = query.value(1).toString();
            wordList[wordIdList::germanDB] = query.value(2).toString();

            ui->checkGermanTranslate->setText(wordList[wordIdList::germanDB]);
        }

        if(frenchEnglish == 1)
        {
            srand(time(0));

            position = rand() % rows;

            QSqlQuery query;

            query.prepare(QString("SELECT frenchTranslation, englishTranslation, germanTranslation FROM words WHERE idWord=:id"));
            query.bindValue(":id", position);
            query.exec();
            query.first();

            wordList[wordIdList::frenchDB] = query.value(0).toString();
            wordList[wordIdList::englishDB] = query.value(1).toString();
            wordList[wordIdList::germanDB] = query.value(2).toString();

            ui->checkFrenchTranslate->setText(wordList[wordIdList::frenchDB]);
            ui->checkEnglishTranslate->setText(wordList[wordIdList::englishDB]);
        }
    }
}

void MainWindow::on_btnCheckTranslate_clicked()
{
    //Allow to save what the user has written
    wordList[wordIdList::frenchUSER] = ui->checkFrenchTranslate->text();
    wordList[wordIdList::englishUSER] = ui->checkEnglishTranslate->text();
    wordList[wordIdList::germanUSER] = ui->checkGermanTranslate->text();

    if(german == 1)
    {
        if(wordList[wordIdList::frenchUSER] != "" && wordList[wordIdList::englishUSER] != "")
        {
            inputDataFormatting();

            if(wordList[wordIdList::frenchUSER] == wordList[wordIdList::frenchDB] && wordList[wordIdList::englishUSER] == wordList[wordIdList::englishDB])
            {
                QMessageBox::information(this, "Result", "Good job ! ");
                fichier(wordList[wordIdList::germanDB]);
                translationVector.push_back(position);
                clearList();
            }
            else
            {
                Answer *answerWindow = new Answer(wordList[wordIdList::frenchDB], wordList[wordIdList::germanDB], wordList[wordIdList::englishDB], this);
                answerWindow->exec();
            }
        }
        else
        {
            QMessageBox::information(this, "Problem", "You need to enter an english and french translation.");
        }
    }
    else if(frenchEnglish == 1)
    {
        if(wordList[wordIdList::frenchUSER] != "" && wordList[wordIdList::germanUSER] != "")
        {
            inputDataFormatting();

            if(wordList[wordIdList::germanDB] == wordList[wordIdList::germanUSER] && wordList[wordIdList::englishDB] == wordList[wordIdList::englishUSER])
            {
                QMessageBox::information(this, "Result", "Good job ! ");
                fichier(wordList[wordIdList::germanDB]);
                translationVector.push_back(position);
                clearList();
            }
            else
            {
                Answer *answerWindow = new Answer(wordList[wordIdList::frenchDB], wordList[wordIdList::germanDB], wordList[wordIdList::englishDB], this);
                answerWindow->exec();
            }
        }
        else
        {
            QMessageBox::information(this, "Problem", "You need to enter an english and german translation.");
        }
    }

}

void MainWindow::on_btnMenuTranslate_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->labelStatusBar->setText("");
}

void MainWindow::on_btnClearTranslate_clicked()
{
    ui->checkEnglishTranslate->clear();
    ui->checkFrenchTranslate->clear();
    ui->checkGermanTranslate->clear();
}

//**************GUESS ARTICLE PAGE**************//
void MainWindow::on_btnCheckArticle_clicked()
{
    //Allow to save what the user has written
    wordList[wordIdList::articleUSER] = ui->articleTranslation->text();
    wordList[wordIdList::frenchUSER] = ui->frenchTranslation->text();

    if(wordList[wordIdList::frenchUSER] != "" && wordList[wordIdList::articleUSER] != "")
    {
        inputDataFormatting();

        if(wordList[wordIdList::articleDB] == wordList[wordIdList::articleUSER] && wordList[wordIdList::frenchDB] == wordList[wordIdList::frenchUSER])
        {
            QMessageBox::information(this, "Result", "Correct translation");
            fichier(wordList[wordIdList::germanDB]);
            articleVector.push_back(positionNoun);
            clearList();
        }
        else
        {
            Answer *answerWindow = new Answer(wordList[wordIdList::frenchDB], wordList[wordIdList::germanDB], wordList[wordIdList::englishDB], wordList[wordIdList::articleDB], wordList[wordIdList::pluralDB], this);
            answerWindow->exec();
        }
    }
    else
    {
        QMessageBox::information(this, "Problem", "You need to enter an english translation and an article (das/der/die).");
    }
}

void MainWindow::on_btnMenuArticle_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->labelStatusBar->setText("");
}

void MainWindow::on_btnGenerateNounArticle_clicked()
{
    QSqlQuery qNoun;
    qNoun.prepare("SELECT COUNT(*) FROM noun");
    qNoun.exec();
    int rows = 0;

    while (qNoun.next())
    {
        rows = qNoun.value(0).toInt();
    }

    if(rows == 0){
        QMessageBox::warning(this, "Database empty", "The database is empty. You must first insert words.");
    }
    else{
        srand(time(0));
        positionNoun = rand() % rows;

        QSqlQuery queryNoun;

        queryNoun.prepare(QString("SELECT article, germanNoun, frenchNoun FROM noun WHERE idNoun=:id"));
        queryNoun.bindValue(":id", positionNoun);
        queryNoun.exec();
        queryNoun.first();

        wordList[wordIdList::articleDB] = queryNoun.value(0).toString();
        wordList[wordIdList::germanDB] = queryNoun.value(1).toString();
        wordList[wordIdList::frenchDB] = queryNoun.value(2).toString();

        ui->nounTranslation->setText(wordList[wordIdList::germanDB]);
    }
}

void MainWindow::on_btnClearArticle_clicked()
{
    ui->articleTranslation->clear();
    ui->frenchTranslation->clear();
    ui->nounTranslation->clear();
}

//**************GUESS PLURAL PAGE**************//
void MainWindow::on_btnMenuPlural_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->labelStatusBar->setText("");
}

void MainWindow::on_btnGenerateNounPlural_clicked()
{
    QSqlQuery qPlural;
    qPlural.prepare("SELECT COUNT(*) FROM noun");
    qPlural.exec();
    int rows = 0;

    while (qPlural.next())
    {
        rows = qPlural.value(0).toInt();
    }

    if(rows == 0){
        QMessageBox::warning(this, "Database empty", "The database is empty. You must first insert words.");
    }
    else{
        srand(time(0));
        positionPlural = rand() % rows;

        QSqlQuery queryNoun;

        queryNoun.prepare(QString("SELECT nounPlurial, germanNoun, frenchNoun FROM noun WHERE idNoun=:id"));
        queryNoun.bindValue(":id", positionPlural);
        queryNoun.exec();
        queryNoun.first();

        wordList[wordIdList::pluralDB] = queryNoun.value(0).toString();
        wordList[wordIdList::germanDB] = queryNoun.value(1).toString();
        wordList[wordIdList::frenchDB] = queryNoun.value(2).toString();

        ui->germanSingularForm->setText(wordList[wordIdList::germanDB]);
    }
}

void MainWindow::on_btnCheckPlural_clicked()
{
    //Allow to save what the user has written
    wordList[wordIdList::pluralUSER] = ui->germanPluralForm->text();
    wordList[wordIdList::frenchUSER] = ui->frenchSingularForm->text();

    if((wordList[wordIdList::pluralUSER] != "") && (wordList[wordIdList::frenchUSER] != ""))
    {
        inputDataFormatting();

        if(wordList[wordIdList::pluralUSER] == wordList[wordIdList::pluralDB] && wordList[wordIdList::frenchUSER] == wordList[wordIdList::frenchDB])
        {
            QMessageBox::information(this, "Result", "Correct translation");
            pluralVector.push_back(positionPlural);
            clearList();
        }
        else
        {
            Answer *answerWindow = new Answer(wordList[wordIdList::frenchDB], wordList[wordIdList::germanDB], wordList[wordIdList::englishDB], wordList[wordIdList::articleDB], wordList[wordIdList::pluralDB], this);
            answerWindow->exec();
        }
    }
    else
    {
        QMessageBox::information(this, "Problem", "You need to enter an english translation and a plural form.");
    }
}

void MainWindow::on_btnClearPlural_clicked()
{
    ui->frenchSingularForm->clear();
    ui->germanPluralForm->clear();
    ui->germanSingularForm->clear();
}

void MainWindow::inputDataFormatting()
{
    wordList[wordIdList::englishUSER] = wordList[wordIdList::englishUSER].toLower();
    wordList[wordIdList::englishUSER][0] = wordList[wordIdList::englishUSER][0].toUpper();
    wordList[wordIdList::germanUSER] = wordList[wordIdList::germanUSER].toLower();
    wordList[wordIdList::germanUSER][0] = wordList[wordIdList::germanUSER][0].toUpper();
    wordList[wordIdList::frenchUSER] = wordList[wordIdList::frenchUSER].toLower();
    wordList[wordIdList::frenchUSER][0] = wordList[wordIdList::frenchUSER][0].toUpper();
    wordList[wordIdList::pluralUSER] = wordList[wordIdList::pluralUSER].toLower();
    wordList[wordIdList::pluralUSER][0] = wordList[wordIdList::pluralUSER][0].toUpper();
    wordList[wordIdList::articleUSER] = wordList[wordIdList::articleUSER].toLower();
    wordList[wordIdList::articleUSER][0] = wordList[wordIdList::articleUSER][0].toUpper();
}

void MainWindow::clearList()
{
    for (int i (0); i < 6; i++)
    {
        wordList[i] = "";
    }
}

//Create a file with all the German words used when using the software
int MainWindow::fichier(QString germanWord)
{
    std::string const words("D://words.txt");
    std::ofstream wordsFlux(words.c_str(), std::ios::app);

    if(wordsFlux)
    {
        wordsFlux << germanWord.toStdString() << "," << std::endl;
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }

    return 0;
}

void MainWindow::on_btnGuessedWordsWindow_clicked()
{

    listGuessedWords *guessedWordWindow = new listGuessedWords(translationVector, articleVector, pluralVector, this);
    guessedWordWindow->exec();
}


void MainWindow::on_btnClearWordAdd_clicked()
{
    ui->addEnglishWord->clear();
    ui->addFrenchWord->clear();
    ui->addGermanWord->clear();
    ui->addArticle->clear();
    ui->addPluralForm->clear();
}
