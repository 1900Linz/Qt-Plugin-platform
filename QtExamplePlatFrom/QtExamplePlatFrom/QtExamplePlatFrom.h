#pragma once

#include <QtWidgets/QMainWindow>
#include <QDockWidget>
#include "ui_QtExamplePlatFrom.h"

class QtExamplePlatFrom : public QMainWindow
{
    Q_OBJECT

public:
    QtExamplePlatFrom(QWidget *parent = Q_NULLPTR);

protected:
    void initMenuActionThings();

    void showConfigPanelWidget();
private:
    Ui::QtExamplePlatFromClass ui;

    QList<QDockWidget*> mItemShowWidgetList;
};
