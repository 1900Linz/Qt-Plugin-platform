#include <QAction>
#include <QPluginLoader>
#include "QtExamplePlatFrom.h"
#include "include/QDataPoolBasic.h"
#include "include/generalPluginBasic.h"

QtExamplePlatFrom::QtExamplePlatFrom(QWidget *parent)
    : QMainWindow(parent)
    , objPluginUtils(nullptr)
    , widgetConfigPanel(nullptr)
{
    ui.setupUi(this);

    auto p = takeCentralWidget();
    if (p)
    {
        delete p;
    }

    setDockNestingEnabled(true);
    initMenuActionThings();
    loadPluginUtils();

}

void QtExamplePlatFrom::initMenuActionThings()
{
    static QAction* actionConfigPanel = new QAction(QStringLiteral("ÅäÖÃ"));
    connect(actionConfigPanel, &QAction::triggered, this, &QtExamplePlatFrom::showConfigPanelWidget);

    ui.menu->addAction(actionConfigPanel);
}

bool QtExamplePlatFrom::loadPluginUtils()
{
    QString Path("utils.dll");
    QPluginLoader pluginLoader(Path);
    objPluginUtils = pluginLoader.instance();
    if (objPluginUtils != NULL)
    {
        auto Port = qobject_cast<generalPlugin*>(objPluginUtils);
        if (Port)
        {
            qDebug() << Path << "is loaded...";
            
            widgetConfigPanel = Port->getWidgetHandler();
            return true;
        }
    }
    else
    {
        qDebug() << Path << "is loaded failed: " << pluginLoader.errorString();
        return false;
    }
}

void QtExamplePlatFrom::showConfigPanelWidget()
{
    if (widgetConfigPanel)
    {
        widgetConfigPanel->show();
    }
}
