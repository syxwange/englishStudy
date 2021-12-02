#ifndef CCUSTOMWORDS_H
#define CCUSTOMWORDS_H

#include <QWidget>
#include "../common.h"

namespace Ui {
class CCustomWords;
}

class CCustomWords : public QWidget
{
    Q_OBJECT

public:
    explicit CCustomWords(QWidget *parent = nullptr);
    ~CCustomWords();

    void slotBtnOK();
signals:
    void signalGetCustomWords(int,QString);
private:
    Ui::CCustomWords *ui;
};

#endif // CCUSTOMWORDS_H
