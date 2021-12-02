
#pragma once

#include <QObject>
#include <QSqlDatabase>
#include "cworddate.h"

class CDatebaseIO : public QObject
{
    Q_OBJECT
public:
    explicit CDatebaseIO(QString name,QObject *parent = nullptr,QString dbFileName="../enWords.db");
    ~CDatebaseIO(){db_.close();}
    void test();
    /**
     * @brief 得到所有要复习的单词
     * 
     * @return QVector<CWord> 要学习的单词数组
     */
    QVector<CLearnedWord> getReviewWords();
    /**
     * @brief Get the Words object得到所有的单词
     * 
     * @return QVector<QStringList> 
     */
    QVector<CWord> getWords( );  
    /**
     * @brief 
     * 
     * @param lw 
     * @return true 
     * @return false 
     */
    bool saveLearnedWords(QMap<QString, CLearnedWord> lw);
    /**
     * @brief Get the All Table Name object得到数据库所有表名
     * 
     * @return QStringList 表名列表
     */
    QStringList getAllTableName();
    /**得到表的列名和类型
     * @brief Get the Table Column object 得到表的列名和类型
     * 
     * @param strTableNmae  表的名字
     * @return QStringList   表的字段数，字段名和字段类型
     */
    QStringList getAllTableColumn(QString strTableNmae);
    
    bool saveWord(const CWord& word);

    bool execSQL(QString strSQL);
 signals:
     void signalErrorMsg(QString);

private:
    QSqlDatabase db_;
    QString  strDBFileName_;
    QString strUserName_;
};




