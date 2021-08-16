#include "answer.h"
#include "ui_answer.h"
#include "iostream"

Answer::Answer(const QString frenchBDD, QString germanBDD, QString englishBDD, QWidget *parent) : QDialog(parent), ui(new Ui::Answer), frenchBDD(frenchBDD), germanBDD(germanBDD), englishBDD(englishBDD)
{
    ui->setupUi(this);
    std::cout << frenchBDD.toStdString() << std::endl;
    std::cout << germanBDD.toStdString() << std::endl;
    std::cout << englishBDD.toStdString() << std::endl;
    //for(int i(0); i < 11; i++)
    //{
     //   wordList[i] = code[i];
     //   std::cout<<"word" <<wordList[i].toStdString()<<std::endl;
    //}
}

Answer::Answer(const QString frenchBDD, const QString germanBDD, const QString englishBDD, const QString articleBDD, const QString pluralBDD, QWidget *parent) : QDialog(parent), ui(new Ui::Answer), frenchBDD(frenchBDD), germanBDD(germanBDD), englishBDD(englishBDD), articleBDD(articleBDD), pluralBDD(pluralBDD)
{
    ui->setupUi(this);
}

Answer::~Answer()
{
    delete ui;
}

void Answer::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->french->setText("French translation : " + frenchBDD);
    ui->german->setText("German translation : " + germanBDD);
    ui->english->setText("English translation : " + englishBDD);
    ui->article->setText("Article : " + articleBDD);
    ui->plural->setText("Plural form : " + pluralBDD);

    //ui->article->text(wordList[]);
    //ui->plural->text(wordList[]);
}
