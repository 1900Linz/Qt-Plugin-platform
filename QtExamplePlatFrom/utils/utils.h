
#ifndef UTILS_H
#define UTILS_H
#pragma once

#include "utils_global.h"
#include "plugin/generalPluginBasic.h"
#include <functional>

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
    utils();
    ~utils();

    void setPluginType(generalPluginTypeEnum plugin_type) Q_DECL_OVERRIDE;
    void getPluginType(generalPluginTypeEnum& plugin_type) Q_DECL_OVERRIDE;

    QWidget* getWidgetHandler() Q_DECL_OVERRIDE;

    void setDataReceiveHandler(generalDataReceive fDataRecv) Q_DECL_OVERRIDE;

private:
    generalPluginTypeEnum _pluginType;
    generalDataReceive  _fdataRecv;
};

#endif // !UTILS_H
