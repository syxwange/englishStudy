#pragma once

#include <QJSEngine>
#include "database/cworddate.h"

struct CSettingInfo
{
    QString  strUsername;
    QStringList strAllUsers;
    QString  strReviewDate;     //复习单词的记忆曲线
    int nWordsCount;
    int nReadWord;
    int nReadGrapheme;
    int nReadChinese;
};

/**
 * @brief 判断动词的过去式是不是特别的
 * 
 * @param word 单词原型 
 * @param strPast  过去式
 * @return true 是特别的，不是正常变化的
 * @return false 是正常变换的
 */
bool getSpecialPast(QString word,QString strPast);

bool getSpecialPL(QString word,QString wordPL);

bool getSpecialDone(QString word,QString wordDone);

bool getSpecialIng(QString word,QString wordIng);

bool getSpecialThird(QString word,QString wordThird);


//js文件执行类
//param:jsFileName ->str  要执行的JS文件路径+名字
class CJSEngine
{
public: 
    CJSEngine(QString jsFileName);

    // 执行JS函数
    // param:strFuncName->str 要执行的函数名
    // param:QJSValueList->QJSValueList js函数需要的参数
    // return: QJSValue  执行js函数返回的值
    QJSValue call(QString strFuncName,QJSValueList args );   

private:
    QJSEngine JsEngine_;
};
