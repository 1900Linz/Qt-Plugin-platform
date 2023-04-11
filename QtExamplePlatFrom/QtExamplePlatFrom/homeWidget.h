#pragma once
#include <qwidget.h>

class QPushButton;
class HomeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HomeWidget(QWidget* parent = (QWidget*)nullptr);

    //static QWidget* instance();

    Q_SIGNAL void signNewSignal(QString filePath);
protected:
    void BtnThing_openFile();

    QPushButton* open;
};

//#define HOME_PAGE homeWidget::instance()