#include "englishsettingwidget.h"
#include "ui_englishsettingwidget.h"
#include <QSettings>
#include <QDebug>

CEnglishSettingWidget::CEnglishSettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CEnglishSettingWidget)
{
    ui->setupUi(this);
}

CEnglishSettingWidget::~CEnglishSettingWidget()
{
    delete ui;

}

void CEnglishSettingWidget::btnOK()
{
    QSettings settings =  QSettings("setting.ini",QSettings::IniFormat);
    // settings.beginGroup("USERNAME");
    // settingInfo_.strUsername = settings.value("user").toString();
    // settings.endGroup();

    // settings.beginGroup(settingInfo_.strUsername);
    // settingInfo_.strReviewDate = settings.value("reviewDate","1 2 4 7 15").toString();
    // settingInfo_.nWordsCount = settings.value("wordCount",10).toInt();
    // settingInfo_.nReadWord = settings.value("readWordCount",0).toInt();
    // settingInfo_.nReadGrapheme = settings.value("readGraphemeCount",0).toInt();
    // settingInfo_.nReadChinese = settings.value("readChineseCount",0).toInt();     
    // settings.endGroup();    
}

// void CEnglishSettingWidget::clicked()
// {
    

// }
