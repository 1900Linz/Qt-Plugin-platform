#include <QAction>
#include <QPluginLoader>
#include <QDir>
#include <QPushButton>
#include "QtExamplePlatFrom.h"
#include "QDataPoolBasic.h"
#include "generalPluginBasic.h"
#include "homeWidget.h"

static QString keyConfig("utils");

QtExamplePlatFrom::QtExamplePlatFrom(QWidget *parent)
    : QMainWindow(parent)
    , objPluginUtils(nullptr)
    , widgetConfigPanel(nullptr)
    , dockManageWidget(new QDockWidget(QStringLiteral("资源管理器"), this))
    , dockDefaultContentWiget(new QDockWidget(QStringLiteral("主页"), this))
    , manageWidget(new QListWidget(dockManageWidget))
    , homeWidget(new HomeWidget(dockManageWidget))
{
    ui.setupUi(this);

    auto p = takeCentralWidget();
    if (p)
    {
        delete p;
    }

    setDockNestingEnabled(true);
    loadPlugin();
    initMenuActionThings();
    initManageWidget();

    dockManageWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dockManageWidget->setMinimumWidth(120);
    dockManageWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    dockManageWidget->setWidget(manageWidget);
    addDockWidget(Qt::LeftDockWidgetArea,dockManageWidget);
    dockDefaultContentWiget->setAllowedAreas(Qt::AllDockWidgetAreas);
    dockDefaultContentWiget->setWidget(homeWidget);
    addDockWidget(Qt::RightDockWidgetArea, dockDefaultContentWiget);

    loadContentDockWidget();
    manageWidget->show();
    dockDefaultContentWiget->show();
}

void QtExamplePlatFrom::initMenuActionThings()
{
    static QAction* actionConfigPanel = new QAction(QStringLiteral("配置"));
    connect(actionConfigPanel, &QAction::triggered, this, &QtExamplePlatFrom::showConfigPanelWidget);

    ui.menu->addAction(actionConfigPanel);
    ui.menu->addSeparator();
    ui.menu->addAction(dockDefaultContentWiget->toggleViewAction());
    ui.menu->addAction(dockManageWidget->toggleViewAction());
}

void QtExamplePlatFrom::initManageWidget()
{
    manageWidget->clear();
    unsigned index = 0;
    for (auto plugin : hashPlugins)
    {
        if (plugin->name == keyConfig)
            continue;

        auto tab = qobject_cast<generalPlugin*>(plugin->pluginL->instance())->getWidgetHandler();
        manageWidget->insertItem(index, plugin->name);

        dockContentWigets.append(new QDockWidget(QString::number(index),this));
        dockContentWigets[index]->setWidget(tab);
        addDockWidget(Qt::RightDockWidgetArea, dockContentWigets[index]);

        index ? tabifyDockWidget(dockContentWigets[index - 1], dockContentWigets[index]) : 0;

        tab->show();

        index++;
    }

    //splitDockWidget(dockDefaultContentWiget, *dockContentWigets.end(),Qt::Horizontal);
    index ? 0: tabifyDockWidget(dockDefaultContentWiget, dockContentWigets[0]);
    dockContentWigets[0]->show();

    
    manageWidget->update();
}

void QtExamplePlatFrom::loadPlugin()
{

    QDir pluginsdir(QDir::currentPath());
    pluginsdir.cd("plugin");

    QFileInfoList pluginsInfo = pluginsdir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    for (QFileInfo info : pluginsInfo)
    {
        auto lib = info.absoluteFilePath();
        if (QLibrary::isLibrary(lib))
        {
            QPluginLoader* loader = new QPluginLoader(lib);
            loader->load();

            auto Port = qobject_cast<generalPlugin*>(loader->instance());
            if (Port)
            {
                auto strname = info.fileName().split(".")[0];
                hashPlugins.insert(strname, new pluginPrivate{ strname , lib , loader});
            }
            else
            {
                delete loader;
                loader = nullptr;
            }
        }
    }

}

void QtExamplePlatFrom::loadContentDockWidget()
{
}

void QtExamplePlatFrom::showConfigPanelWidget()
{

    if (!widgetConfigPanel)
    {
        auto thisPluginInfo = hashPlugins.value("utils");
        if (thisPluginInfo->name == keyConfig)
        {
            widgetConfigPanel = qobject_cast<generalPlugin*>(thisPluginInfo->pluginL->instance())->getWidgetHandler();
        }
        else
        {
            return;
        }
    }

    widgetConfigPanel->show();

}
