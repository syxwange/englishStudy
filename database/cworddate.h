#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QMap>


struct CWord
{
    int id;
    QString word;                       //单词原型
    QString phAM;                     //音标
    QVector<QString> parts;     //词性，汉语翻译
    QString memorySkill;           //记忆技巧
    QString strParts;
    QMap<QString,QString>     exchange;
  
};

struct CLearnedWord
{
    int id;
    QString word;
    QString dateTime;
    int errorCount;
    int count ;
};

struct CSettingInfo;

class CWordDate:public QObject
{
    Q_OBJECT
public:
    CWordDate(CSettingInfo* user, QObject *parent = nullptr);
    ~CWordDate(){}
    void test();
 
    void slotGetWord(int num,QString strText);
    /**
     * @brief 保存学习的单词各种信息
     * 
     * @param lw 学习的单词数组    
     */
    void slotSaveLearnedWords(QVector<CLearnedWord> lw);

signals:
    void signalShowWord(QVector<CWord> words);
    void signalError(QString err);

private:
    /**
     * @brief 解析json格式单词
     * 
     * @return CWord 
     */
    //CWord wordFronJson(QString );

    void getReviewWords(const QVector<CLearnedWord>&);

private:
    QMap<QString,CLearnedWord> mLw_;    
    CSettingInfo * pSettingInfo_;
};
