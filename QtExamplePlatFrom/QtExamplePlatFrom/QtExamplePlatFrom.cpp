#include <QAction>
#include "QtExamplePlatFrom.h"


QtExamplePlatFrom::QtExamplePlatFrom(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    auto p = takeCentralWidget();
    if (p)
    {
        delete p;
    }

    setDockNestingEnabled(true);
}

void QtExamplePlatFrom::initMenuActionThings()
{
    static QAction* actionConfigPanel = new QAction("≈‰÷√");
    connect(actionConfigPanel, &QAction::triggered, this, &QtExamplePlatFrom::showConfigPanelWidget);
}
