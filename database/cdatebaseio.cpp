#include "cdatebaseio.h"
#include <QSqlError>
#include <QSqlQuery>

#include <QFileInfo>


CDatebaseIO::CDatebaseIO(QString name,QObject *parent,QString dbFileName) : strUserName_(name), QObject(parent),
    strDBFileName_(dbFileName)
{     
    if (!QFileInfo::exists(strDBFileName_))         
    {
        emit signalErrorMsg("没有找到数据库文件");
        return;
    }

    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db_=QSqlDatabase::database("qt_sql_default_connection");
    else     db_ = QSqlDatabase::addDatabase("QSQLITE");
        
    db_.setDatabaseName(strDBFileName_);    
    db_.open();    
}

QStringList CDatebaseIO::getAllTableName()
{
    return db_.tables();
}

QStringList CDatebaseIO::getAllTableColumn(QString strTableNmae )
{
    QString str = "PRAGMA table_info(" + strTableNmae + ")";
    QSqlQuery query;
    query.prepare(str);
    QStringList  tableColumn; 
    if (query.exec())  
        while (query.next())     
            tableColumn.append( QString("字段数:%1     字段名:%2     字段类型:%3").arg(query.value(0).toString()).arg(query.value(1).toString()).arg(query.value(2).toString()));
       
    return tableColumn;
}

QVector<CLearnedWord> CDatebaseIO::getReviewWords()
{
    QVector<CLearnedWord> words;
    QSqlQuery query;   
    auto strSQL = QString("SELECT * FROM %1").arg(strUserName_);
    query.prepare(strSQL);    
    if (query.exec())
    {       
         while (query.next())
        {
            CLearnedWord temp;
            temp.dateTime = query.value(1).toString();
            temp.errorCount= query.value(2).toInt();
            temp.word = query.value(3).toString();
            temp.count = query.value(4).toInt();
            temp.id = query.value(0).toInt();
            words.append(temp);        
        }
    }
    return words;
}

QVector<CWord> CDatebaseIO::getWords()
{
    QSqlQuery query;
    QVector<CWord> words;    
    auto strSQL = QString("SELECT * FROM cwords ORDER BY RANDOM()");
    query.prepare(strSQL);    
    if (query.exec())
    {       
         while (query.next())
        {  
            CWord w;
            w.id = query.value(0).toInt();   
            w.word=query.value(1).toString();
            w.phAM=query.value(2).toString(); 
            w.strParts=query.value(3).toString(); 
            w.memorySkill=query.value(4).toString();
            auto keys = query.value(5).toString().split(";");
            auto values= query.value(6).toString().split(";");
            for (int i=0;i<keys.count();i++)       w.exchange[keys[i]]=values[i];                  
            words.append(w);
        }
    }
    return words;
}

bool CDatebaseIO::saveLearnedWords(QMap<QString, CLearnedWord> lw)
{  
    QSqlQuery query;
    QString strSQL;
    for(auto & item:lw)
    {       
        if(item.count==1)
            strSQL = QString("INSERT INTO %1 VALUES (NULL ,'%2',%3,'%4',%5)").arg(strUserName_).arg(item.dateTime).arg(item.errorCount).arg(item.word).arg(item.count);
        else
            strSQL = QString("UPDATE %1 SET  dateVector='%2' ,errorCount=%3 ,count=%4  WHERE ID=%5").arg(strUserName_).arg(item.dateTime).arg(item.errorCount).arg(item.count).arg(item.id);
        query.prepare(strSQL);
        if(!query.exec())       
            return false;      
    }
    db_.commit();
    return true;
}

// "CREATE TABLE IF NOT EXISTS englishWords(id INT PRIMARY KEY AUTOINCREMENT,word TEXT,phAm TEXT,parts TEXT,memorySkill TEXT,exchange TEXT,exchangeValue TEXT)";
bool CDatebaseIO::saveWord(const CWord& w)
{
    QString strSQL;
    if(w.id==0)
        strSQL = QString(" INSERT INTO cwords VALUES (NULL,'%1' ,'%2','%3','%4','%5','%6')").arg(w.word).arg(w.phAM).arg(w.parts.join(";")).arg(w.memorySkill).arg(w.exchange.keys().join(";")).arg(w.exchange.values().join(";"));
    else
        strSQL = QString("REPLACE  INTO cwords VALUES ('%1,'%2','%3','%4','%5','%6','%7)").arg(w.id).arg(w.word).arg(w.phAM).arg(w.parts.join(";")).arg(w.memorySkill).arg(w.exchange.keys().join(";")).arg(w.exchange.values().join(";"));
    return execSQL(strSQL);
}

void CDatebaseIO::test()
{    
   auto sql ="CREATE TABLE IF NOT EXISTS cwords (id INTEGER  PRIMARY KEY  AUTOINCREMENT,word TEXT,phAm TEXT,parts TEXT,memorySkill TEXT,exchange TEXT,exchangeValue TEXT)";
   qDebug()<< execSQL(sql);
   
}

bool CDatebaseIO::execSQL(QString strSQL)
{
    QSqlQuery query;
    query.prepare(strSQL);
    return query.exec();
}

//select * from A where aa like in(%1%);
//SELECT * FROM A a WHERE a.aa like '1,%' or a.aa like '%,1,%' or a.aa like '%,1'
//SELECT 学生表.姓名,学生表.性别,学生表.民族,成绩表.字段2,成绩表.字段3  FROM 学生表,成绩表  WHERE 学生表.姓名 = 成绩表.姓名  AND 学生表.性别 = '男'  AND 成绩表.字段3 > 36
//SELECT 学生表.*,成绩表.*  FROM 学生表,成绩表  WHERE 学生表.姓名 = 成绩表.姓名  AND 学生表.性别 = '男'  AND 成绩表.字段3 > 36
//SELECT key,value FROM dict ORDER BY RANDOM(key) LIMIT 1
//CREATE TABLE COMPANY(  ID INT PRIMARY KEY   NOT NULL,  NAME   TEXT   NOT NULL,   AGE  INT   NOT NULL, ADDRESS   CHAR(50),  SALARY    REAL);