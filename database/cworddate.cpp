
#include "cworddate.h"
#include "cdatebaseio.h"
#include <QDateTime>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "../common.h"

CWordDate::CWordDate(CSettingInfo* user, QObject *parent ):QObject(parent),pSettingInfo_(user)
{
}

void CWordDate::slotGetWord(int num,QString strText)
 {
    CDatebaseIO db(pSettingInfo_->strUsername);
    QVector<CWord> words;
    int nNewWords = 0;
    auto allWords = db.getWords();    
    auto learnedWords = db.getReviewWords();

    if(num==0)          //自定义单词学习 
        for(auto &i:strText.split(","))         
            mLw_[i]={0,i,"",0,1};

    //得到要复习的单词 学习记录
    getReviewWords(learnedWords);
   
    //得到要学习的单词（新单词或自定义单词+要复习的单词
    for(auto & word:allWords)     
    {
        if(mLw_.contains(word.word))   //通过单词学习记录得到要复习+自定义单词
        {
            //auto temp = wordFronJson(word[1]); 
            words.append(word);
        }
        else if(nNewWords<num)      //得到要学习的新单词
        {
            nNewWords++;
            //auto temp = wordFronJson(word[1]); 
            words.append(word);
        }
    }  
    
    emit signalShowWord(words);  
 }

 void CWordDate::getReviewWords(const QVector< CLearnedWord>& learnedWords)
 {
    for(auto& lw:learnedWords)
    {
        //得到最后一次学习日期和当前日期相差天数
        QString dateStr = lw.dateTime.split(",").last();                          
        auto date = QDateTime::fromString(dateStr,"yyyy-MM-dd");            
        int days = date.daysTo(QDateTime::currentDateTime());          

        auto reviewDay = pSettingInfo_->strReviewDate.split(" ");
        for(int i=1;i<=reviewDay.count();i++)          
            if(lw.count==i&&days>=reviewDay[i-1].toInt())
                mLw_[lw.word]=lw; 
    }
 }

void CWordDate::slotSaveLearnedWords(QVector<CLearnedWord> lw)
{
    CDatebaseIO db(pSettingInfo_->strUsername);
    for(auto & item:lw)
    {
        mLw_[item.word].dateTime+=","+item.dateTime;
        mLw_[item.word].errorCount += item.errorCount;
        mLw_[item.word].count += item.count;
    }
    if(!db.saveLearnedWords(mLw_))
        emit signalError("save learned words error"); 
}

void CWordDate::test()
{   
    
 
}

// CWord CWordDate::wordFronJson(QString strJson)
// {   
//     CWord tempWord;
//     strJson.replace(": None",": \"\"");           
//     auto  jsonDoc = QJsonDocument::fromJson(strJson.toUtf8());        
//     tempWord.memorySkill = jsonDoc["memory_skill"].toString();  
//     tempWord.word = jsonDoc["word_name"].toString();  
//     auto exchange = jsonDoc["exchange"].toObject();
//     tempWord.wordThird =exchange["word_third"].toArray()[0].toString();
//     tempWord.wordIng =exchange["word_ing"].toArray()[0].toString();
//     tempWord.wordDone =exchange["word_done"].toArray()[0].toString();
//     tempWord.wordPast =exchange["word_past"].toArray()[0].toString();
//     tempWord.wordPL =exchange["word_pl"].toArray()[0].toString();
//     tempWord.wordEr =exchange["word_er"].toArray()[0].toString();
//     tempWord.wordEst =exchange["word_est"].toArray()[0].toString();
//     auto symbols = jsonDoc["symbols"].toArray(); 
//     for(auto item:symbols)
//     {
//         tempWord.phAM =  item.toObject()["ph_am"].toString();
//         auto parts = item.toObject()["parts"].toArray();
//         for(auto itemParts:parts)
//         {               
//             QString temp;
//             temp += itemParts.toObject()["part"].toString()+" ";
//             auto means = itemParts.toObject()["means"].toArray();                    
//             for(auto itemMeans:means)               
//                 temp += itemMeans.toString()+" ";     
//             tempWord.parts.append(temp);
//         }
//     }  
//     return tempWord; 
// }