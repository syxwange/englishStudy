#include "cenglishstudy.h"
#include <QSettings>


CEnglishStudy::CEnglishStudy(QObject *parent) : QObject(parent)
{
    loadSetting();
}

CEnglishStudy::~CEnglishStudy()
{
    saveSetting();
    if(pMainWindow_)
        delete pMainWindow_;
    if(pWordDate_)
        delete pWordDate_;        
}

void CEnglishStudy::show()
{
    pWordDate_ =new CWordDate(&settingInfo_);
    pMainWindow_ = new MainWindow(&settingInfo_);
    connect(pMainWindow_,MainWindow::signalSaveLearnedWords,pWordDate_,CWordDate::slotSaveLearnedWords);
    connect(pWordDate_,CWordDate::signalError,pMainWindow_,MainWindow::slotShowError);
    connect(pMainWindow_,MainWindow::signalGetWords,pWordDate_,CWordDate::slotGetWord);
    connect(pWordDate_,CWordDate::signalShowWord,pMainWindow_,MainWindow::slotShowWords);
    connect(pMainWindow_,MainWindow::signalSaveLearnedWords,pWordDate_,CWordDate::slotSaveLearnedWords);
    pMainWindow_->show();
}

void CEnglishStudy::test()
{
    pWordDate_->test();
}

void CEnglishStudy::loadSetting()
{
    QSettings settings =  QSettings("setting.ini",QSettings::IniFormat);
    settings.beginGroup("USERNAME");
    settingInfo_.strUsername = settings.value("user","WangCeiLin").toString();
    settingInfo_.strAllUsers = settings.value("allUser").toStringList();
    settings.endGroup();

    settings.beginGroup(settingInfo_.strUsername);
    settingInfo_.strReviewDate = settings.value("reviewDate","1 2 4 7 15").toString();
    settingInfo_.nWordsCount = settings.value("wordCount",10).toInt();
    settingInfo_.nReadWord = settings.value("readWordCount",0).toInt();
    settingInfo_.nReadGrapheme = settings.value("readGraphemeCount",0).toInt();
    settingInfo_.nReadChinese = settings.value("readChineseCount",0).toInt();     
    settings.endGroup();    
}

void CEnglishStudy::saveSetting()
{
    if(!settingInfo_.strAllUsers.contains(settingInfo_.strUsername))
        settingInfo_.strAllUsers.append(settingInfo_.strUsername);
    QSettings settings =  QSettings("setting.ini",QSettings::IniFormat);
    settings.beginGroup("USERNAME");
    settings.setValue("user",settingInfo_.strUsername);
    settings.setValue("allUser",settingInfo_.strAllUsers);
    settings.endGroup();
 
    settings.beginGroup(settingInfo_.strUsername);
    settings.setValue("reviewDate",settingInfo_.strReviewDate);
    settings.setValue("wordCount",settingInfo_.nWordsCount);
    settings.setValue("readWordCount",settingInfo_.nReadWord);
    settings.setValue("readGraphemeCount",settingInfo_.nReadGrapheme);
    settings.setValue("readChineseCount",settingInfo_.nReadChinese);
    settings.endGroup();  
}