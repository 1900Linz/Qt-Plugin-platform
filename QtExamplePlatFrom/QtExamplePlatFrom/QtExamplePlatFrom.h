#pragma once

#include <QtWidgets/QMainWindow>
#include <QDockWidget>
#include <QListWidget>
#include "ui_QtExamplePlatFrom.h"

class HomeWidget;
class QPluginLoader;
struct pluginPrivate
{
    QString name;
    QString path;
    QPluginLoader* pluginL;
};

class QtExamplePlatFrom : public QMainWindow
{
    Q_OBJECT

public:
    QtExamplePlatFrom(QWidget *parent = Q_NULLPTR);

protected:
    void initMenuActionThings();

    void initManageWidget();

    void loadPlugin();

    void loadContentDockWidget();

    void showConfigPanelWidget();

private:
    Ui::QtExamplePlatFromClass ui;

    QObject* objPluginUtils;

    QWidget* widgetConfigPanel;

    QDockWidget* dockManageWidget;

    QDockWidget* dockDefaultContentWiget;

    QList<QDockWidget*> dockContentWigets;

    QListWidget* manageWidget;

    HomeWidget* homeWidget;

    QHash<QString, pluginPrivate*> hashPlugins;
};
