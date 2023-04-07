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

    bool loadPluginUtils();

    void showConfigPanelWidget();
private:
    Ui::QtExamplePlatFromClass ui;

    QList<QDockWidget*> mItemShowWidgetList;

    QObject* objPluginUtils;

    QWidget* widgetConfigPanel;
};
