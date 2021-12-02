#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include "englishsettingwidget.h"
#include <QBoxLayout>
#include <QMessageBox>
#include   "cwordstudywidget.h"
#include <QDebug>
#include <QLineEdit>
#include <QPushButton>
#include "CCustomWords.h"

MainWindow::MainWindow(CSettingInfo *settingInfo,QWidget *parent) : QMainWindow(parent)  , ui(new Ui::MainWindow),pSettingInfo_(settingInfo)
{
    ui->setupUi(this);  

    connect(ui->actSetting,QAction::triggered,this,MainWindow::actEnglishSetting);
    connect(ui->actWords,QAction::triggered,this ,MainWindow::actWordStudy);
    connect(ui->actCustom,QAction::triggered,this ,MainWindow::actCustomWords);
    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actEnglishSetting(bool checked = false)
{
    CEnglishSettingWidget* enSetting = new CEnglishSettingWidget(this) ;
    setCentralWidget(enSetting);   
}

void MainWindow::actWordStudy(bool checked = false)
{
    emit signalGetWords(pSettingInfo_->nWordsCount,pSettingInfo_->strUsername);
}

void MainWindow::slotShowError(QString err)
{
    QMessageBox::warning( dynamic_cast<QWidget *>(this),"error",err);  
}

void MainWindow::actCustomWords()
{
    auto * pCustomWords = new CCustomWords(this);    
    connect(pCustomWords,CCustomWords::signalGetCustomWords,this,MainWindow::signalGetWords);
    setCentralWidget(pCustomWords);
}


void MainWindow::slotShowWords(QVector<CWord> words)
{
    auto * pShowWords = new CWordStudyWidget(this);
    connect(pShowWords,CWordStudyWidget::signalStrudyOver,this,MainWindow::signalSaveLearnedWords);
    pShowWords->init(words);
    setCentralWidget(pShowWords);
}

