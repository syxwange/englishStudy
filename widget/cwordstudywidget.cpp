#include "cwordstudywidget.h"
#include "ui_cwordstudywidget.h"
#include <random>
#include <QDateTime>
#include <QMessageBox>


CWordStudyWidget::CWordStudyWidget(QWidget *parent) :  QWidget(parent), ui(new Ui::CWordStudyWidget)
{
    ui->setupUi(this);
    ui->labelWord->setStyleSheet("color:blue;font: bold; font-size:22px;");
    ui->labelSoundmark->setStyleSheet("color:black;font-size:16px;");
    ui->labelChinese->setStyleSheet("color:black;font-size:14px;");
    ui->labelChinese->setWordWrap(true);
    ui->labelDistortion->setStyleSheet("color:red");
    ui->labelDistortion->setWordWrap(true);
    ui->btnNext->setFocus();
    ui->btnNext->setShortcut(QKeySequence::MoveToNextChar );
    ui->btnPre->setShortcut(QKeySequence::MoveToPreviousChar);
    ui->btnPratice->setVisible(false);
    ui->btnTest->setVisible(false);
    ui->rbs->setVisible(false);
    ui->lineEdit->setVisible(false);


    connect(ui->btnNext,QPushButton::clicked,this,CWordStudyWidget::slotBtnNext);
    connect(ui->btnPre,QPushButton::clicked,this,CWordStudyWidget::slotBtnPre);
    connect(ui->btnPratice,QPushButton::clicked,this,CWordStudyWidget::slotBtnPratice);
    connect(ui->btnTest,QPushButton::clicked,this,CWordStudyWidget::slotBtnTest);
}

CWordStudyWidget::~CWordStudyWidget()
{
    delete ui;
}

void CWordStudyWidget::slotBtnNext()
{
    if(type_==TYPE::pratice)
    {
        int nError = 1;
        auto strWord = words_[nCurrent_].word;        
        if((ui->rb1->isChecked()&& ui->rb1->text()==strWord)||(ui->rb2->isChecked()&& ui->rb2->text()==strWord)||
                (ui->rb3->isChecked()&& ui->rb3->text()==strWord)||(ui->rb4->isChecked()&& ui->rb4->text()==strWord))          
            nError = 0; 
        mLW_[strWord]=CLearnedWord{0,strWord,"strDate",nError,1};
    }
    if(type_==TYPE::test)
    {
        auto strDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
        CLearnedWord lw{0,words_[nCurrent_].word,strDate,1,1};   
        if(ui->lineEdit->text()==words_[nCurrent_].word)         lw.errorCount=0;     
        mLW_[ui->lineEdit->text()+words_[nCurrent_].word]= lw;
    }

    if(nCurrent_+1<words_.count()) 
    {
        if(!ui->btnPre->isEnabled())        ui->btnPre->setEnabled(true);  
        nCurrent_++;
        showWord(nCurrent_);
    }else
    {
        ui->btnNext->setVisible(false);
        if(type_==TYPE::learn)
        {
            ui->btnPratice->setVisible(true);   
            ui->btnPratice->setFocus();
        }        
        else if(type_==TYPE::pratice)
        {
            ui->btnTest->setVisible(true);
            ui->btnTest->setFocus();
            ui->btnPre->setVisible(false);
            ui->rbs->setVisible(false);
            QString strTemp;
            for(auto  &item:mLW_)
            {
               if(item.errorCount==1)
               {
                    strTemp += item.word+"\n";
                    for(auto & i:words_)
                        if(item.word==i.word)
                            strTemp += i.parts.join("\n")+"\n";
                    strTemp += "\n";
               }                   
            }    
            ui->scrollArea->setFixedHeight(300); 
            ui->labelChinese->setText(strTemp);
        }            
        else
        {
            QString tempstr;
            QVector<CLearnedWord> lw;
            for(auto & i :mLW_.keys())
            {
                if(i!=mLW_[i].word+mLW_[i].word)
                {
                    tempstr +=mLW_[i].word+"---"+i.left(i.count()-mLW_[i].word.count())+'\n';
                    ui->scrollArea->setFixedHeight(300); 
                    ui->labelChinese->setText(tempstr);
                    ui->lineEdit->setVisible(false) ;
                }
                lw.append(mLW_[i]);
            }           
            emit signalStrudyOver( lw);        
        }            
    }     
}

void CWordStudyWidget::slotBtnPre()
{
    if(nCurrent_>0) 
    {
        if(!ui->btnNext->isVisible())
        {
            ui->btnNext->setVisible(true);
            ui->btnTest->setVisible(false); 
            ui->btnPratice->setVisible(false);   
        }            
        nCurrent_--;
        showWord(nCurrent_);
    }else
        ui->btnPre->setDisabled(true);  
}

void CWordStudyWidget::init(QVector<CWord> words)
{
    words_=words;     
    ui->labelMessage->setText(QString("学习单词数量：%1").arg(words_.count()));
    showWord();
}

void CWordStudyWidget::slotBtnPratice()
{
    nCurrent_=0;
    type_=TYPE::pratice;
    ui->btnNext->setVisible(true);
    ui->btnPratice->setVisible(false);   
    ui->btnPre->setDisabled(true);
    ui->labelWord->setVisible(false);
    ui->labelSoundmark->setVisible(false);
    ui->labelDistortion->setVisible(false);
    ui->rbs->setVisible(true);
    std::random_shuffle(words_.begin(), words_.end());    
    showWord();
}

void CWordStudyWidget::slotBtnTest()
{
    mLW_.clear();
    nCurrent_=0;
    type_=TYPE::test;
    ui->scrollArea->setFixedHeight(180);     
    ui->btnNext->setVisible(true);
    ui->btnTest->setVisible(false);   
    ui->btnPre->setVisible(false);
    ui->labelWord->setVisible(false);
    ui->labelSoundmark->setVisible(false);
    ui->labelDistortion->setVisible(false);
    ui->rbs->setVisible(false);
    ui->lineEdit->setVisible(true);
    ui->lineEdit->setFocus();
    connect(ui->lineEdit,QLineEdit::returnPressed,this,CWordStudyWidget::slotBtnNext);
     ui->btnNext->setShortcut(QKeySequence::InsertParagraphSeparator);
    std::random_shuffle(words_.begin(), words_.end());    
    showWord();   
}

void CWordStudyWidget::showWord(int n)
{
    nCurrent_=n;
    ui->labelMessage->setText(QString("单词总数量：%1 当前为：%2").arg(words_.count()).arg(n+1));
    ui->labelChinese->setText(words_[n].strParts.replace(";","\n"));    
   
    if(type_== TYPE::learn)
    {
        QString  strExchange ;
       
        if(getSpecialPast(words_[n].word,words_[n].exchange["wordPast"]))
            strExchange +="过去式："+ words_[n].exchange["wordPast"]+"；";
             
        ui->labelWord->setText(words_[n].word);    
        ui->labelSoundmark->setText("["+words_[n].phAM+"]");     
        ui->labelDistortion->setText(strExchange.left(strExchange.count()-1));             
    }

    if(type_== TYPE::pratice)
    {
        QVector<CWord> answer;       
        auto temp = words_;
        std::random_shuffle(temp.begin(), temp.end());        
        for(int i=0;i<4;i++)
        {
            if(words_[n].word!=temp[i].word)       answer.append(temp[i]);
            if(answer.count()==3)       break;
        }
        answer.append(words_[nCurrent_]);
        std::random_shuffle(answer.begin(), answer.end());

        QRadioButton * rbs[]{ui->rb1,ui->rb2,ui->rb3,ui->rb4};
        for(int i=0;i<4;i++)
        {
            rbs[i]->setText(answer[i].word);
            rbs[i]->setCheckable(false);
            rbs[i]->setCheckable(true);
        } 
    }

    if(type_== TYPE::test)      ui->lineEdit->setText("");
}