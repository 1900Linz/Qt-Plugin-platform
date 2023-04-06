#ifndef GENERALBASIC_PLUGIN_H
#define GENERALBASIC_PLUGIN_H

#include <QtPlugin>
#include <QVariant>
#include <QList>

#define QTPLUGHIN_GENERALBASICPORT_IID "qtexampleplatform.plugin.interface.generalbasicport"

typedef std::function<void(const QVariant*)> generalDataReceive;

enum generalPluginTypeEnum
{
	WithWidget = 0,
	WithoutWidget
};

class generalPlugin {
public:
	virtual ~generalPlugin() {}

	virtual void setPluginType(generalPluginTypeEnum plugin_type) = 0;
	virtual void getPluginType(generalPluginTypeEnum& plugin_type) = 0;

	virtual QWidget* getWidgetHandler() = 0;

	virtual void setDataReceiveHandler(generalDataReceive fDataRecv) = 0;
};

Q_DECLARE_INTERFACE(generalPlugin, QTPLUGHIN_GENERALBASICPORT_IID)

#endif // !GENERALBASIC_PLUGIN_H
