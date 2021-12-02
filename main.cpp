
#include <QApplication>
#include <QJSEngine>
#include <QFile>
#include <QDebug>
#include "common.h"
#include <QBitArray>

#include   "cenglishstudy.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  

    CEnglishStudy  w;   
    w.show();  
    w.test();
    return a.exec();   
}
