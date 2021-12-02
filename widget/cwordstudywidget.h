#pragma once

#include <QWidget>
#include "../common.h"

namespace Ui {
class CWordStudyWidget;
}

class CWordStudyWidget : public QWidget
{
    Q_OBJECT
    
public:

    enum class TYPE{learn,pratice,test};
    explicit CWordStudyWidget(QWidget *parent = nullptr);
    ~CWordStudyWidget();

    void init(QVector<CWord> words);
public slots:
    void slotBtnNext();
    void slotBtnPre();
    void slotBtnPratice();
    void slotBtnTest();
    
signals:
    void signalStrudyOver(QVector<CLearnedWord> );
private:
    void showWord(int n = 0);

private:
    Ui::CWordStudyWidget *ui;
    QVector<CWord> words_;   
    int nCurrent_ = 0;
    TYPE type_{TYPE::learn};
    QMap<QString,QString> mExchange_{{"wordPL","复数："},{"wordThird","第三人称单数："},{"wordIng","现在分词："},{"wordPast","过去式："},{"wordDone","过去分词："},{"wordEst","最高级："},{"wordEr","比较级："}};
    QMap<QString,CLearnedWord> mLW_;
};


