#ifndef ENGLISHSETTINGWIDGET_H
#define ENGLISHSETTINGWIDGET_H

#include <QWidget>

namespace Ui {
class CEnglishSettingWidget;
}

class CEnglishSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CEnglishSettingWidget(QWidget *parent = nullptr);
    ~CEnglishSettingWidget();

    Ui::CEnglishSettingWidget *ui;

public slots:
    void btnOK();
    
private:
    
};

#endif // ENGLISHSETTINGWIDGET_H
