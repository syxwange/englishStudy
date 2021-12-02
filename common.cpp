#include "common.h"

#include <QFile>

CJSEngine::CJSEngine(QString jsFileName)
{
    QString strJsFilePath = "../baiduTranslate.js";
    QFile scriptFile(strJsFilePath);
    if (!scriptFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Load Js File Failed, FilePath:"<< strJsFilePath;
        return  ;
    }        
    QString jsContents =  scriptFile.readAll(); 
    scriptFile.close();  
    JsEngine_.evaluate(jsContents, strJsFilePath);
}

QJSValue CJSEngine::call(QString strFuncName,QJSValueList args )
{
    QJSValue Jsfunc = JsEngine_.globalObject().property(strFuncName);  
    return Jsfunc.call(args);
}

bool getSpecialPast(QString word,QString wordPast)
{
    if(wordPast.isEmpty()||word+"ed"==wordPast)
        return false;   

    if(word.last(1)=="e"&&word+"d"==wordPast) 
        return false;

    if(word.last(1)=="y"&&word.left(word.count()-1)+"ied"==wordPast)
        return false;    
   
    auto ret = word[word.count()-2];
    if((ret=='a'||ret=='o'||ret=='e'||ret=='i'||ret=='u')&&(word+ word.last(1)+"ed"==wordPast))
        return false;    
    return true;  
}

bool getSpecialDone(QString word,QString wordDone)
{
    return getSpecialPast(word,wordDone);
}

bool getSpecialThird(QString word,QString wordThird)
{
    return getSpecialPL(word,wordThird);
}

bool getSpecialIng(QString word,QString wordIng)
{
    
    //1、 一般在词尾加-ing(一般-ing)。
    if(wordIng.isEmpty()||word+"ing"==wordIng)
        return false; 

    //2、 以不发音的字母e结尾，先去e再加-ing(去哑e)。例如：making，arriving，coming。
    if(word.last(1)=="e"&&word.left(word.count()-1)+"ing"==wordIng)
        return false;

    //3、 以重读闭音节结尾，且词尾只有一个辅音字母时，先双写这个辅音字母，再加-ing(重闭单辅先双写)。例如：running，stopping，preferring。
    auto ret = word[word.count()-2];
    if((ret=='a'||ret=='o'||ret=='e'||ret=='i'||ret=='u')&&(word+ word.last(1)+"ing"==wordIng))
        return false;  

    //4、 以-ie结尾，先将-ie改成y，再加-ing。例如：tying，dying, lying。
    if((word.last(2)=="ie")&&word.left(word.length() - 2)+"ying"==wordIng) 
        return false;
    
    return true;
}

bool getSpecialPL(QString word,QString wordPL)
{
    //在名词词尾加s: car-cars, book-books
    if(wordPL.isEmpty()||word+"s"==wordPL)
        return false;

    //以s, x, ch, sh结尾的可数名词，在词尾加es.
    if((word.last(1)=="s"||word.last(1)=="x"||word.last(2)=="sh"||word.last(2)=="ch")&&word+"es"==wordPL)
        return false;

    //以“辅音字母+y”结尾的可数名词，变y为i再加es.    
    if(word.last(1)=="y"&&word.left(word.length()-1)+"ies"==wordPL)
        return false;        

    //以f或fe结尾的可数名词，变f或fe为v，再加es。
    if((word.last(1)=="f")&&word.left(word.length() - 1)+"ves"==wordPL)
        return false;
    if((word.last(2)=="fe")&&word.left(word.length() - 2)+"ves"==wordPL) 
        return false;

    return true;       
}