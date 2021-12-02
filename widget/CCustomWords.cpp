#include "CCustomWords.h"
#include "ui_CCustomWords.h"

CCustomWords::CCustomWords(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CCustomWords)
{
    ui->setupUi(this);
    connect(ui->pushButton,QPushButton::clicked,this,CCustomWords::slotBtnOK);
}

CCustomWords::~CCustomWords()
{
    delete ui;
}

void CCustomWords::slotBtnOK()
{
    emit signalGetCustomWords(0,ui->lineEdit->text());
}
