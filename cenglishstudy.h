#ifndef CENGLISHSTUDY_H
#define CENGLISHSTUDY_H

#include <QObject>
#include "common.h"
#include "widget/mainWindow.h"

class CEnglishStudy : public QObject
{
    Q_OBJECT

public:
    explicit CEnglishStudy(QObject *parent = nullptr);
    ~CEnglishStudy();
    void show();
    void test();

    /**
     * @brief 得到要学习的单词数组
     * 
     * @return void 
     */
    void  getWords();

    bool saveLearnedWords(QVector<CLearnedWord> lw);

signals:
    void signalShowWords(QVector<CWord>);

private:
    //load  setting.ini file
    void loadSetting();
    void saveSetting();

private:
    MainWindow * pMainWindow_=nullptr;
    CSettingInfo settingInfo_;
    CWordDate * pWordDate_=nullptr;
};

#endif // CENGLISHSTUDY_H
