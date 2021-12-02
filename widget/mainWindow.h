#pragma once

#include <QMainWindow>
#include "../common.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(CSettingInfo* settingInfo,QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void signalSaveLearnedWords(QVector<CLearnedWord> lw);
    void signalGetWords(int num,QString user);
    
public slots: 
    void actEnglishSetting(bool);
    void actWordStudy(bool );
    void actCustomWords();
    
    void slotShowError(QString err);
    void slotShowWords(QVector<CWord> words);
    
    

private:


private:
    Ui::MainWindow *ui;    
    CSettingInfo * pSettingInfo_;
};

