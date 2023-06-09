
#ifndef UTILS_H
#define UTILS_H
#pragma once

#include "utils_global.h"
#include "generalPluginBasic.h"
//#include "QDataPoolBasic.h"

using namespace std;

class UTILS_EXPORT utils :
    public QObject,
    public generalPlugin
{
    Q_OBJECT
        /*
        使用Q_INTERFACES声明：类支持ISerialPort
        */
        Q_INTERFACES(generalPlugin)

#if QT_VERSION >= 0x05000
        Q_PLUGIN_METADATA(IID QTPLUGHIN_GENERALBASICPORT_IID)
#endif

public:
    explicit utils(generalPluginTypeEnum plugin_type = WithWidget);
    ~utils();

    void getPluginType(generalPluginTypeEnum& plugin_type) Q_DECL_OVERRIDE;

    QWidget* getWidgetHandler() Q_DECL_OVERRIDE;

    void handleData(QVariant);

private:
    generalPluginTypeEnum _pluginType;
//    generalDataReceive  _fdataRecv;
};

#endif // !UTILS_H
