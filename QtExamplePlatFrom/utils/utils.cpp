#include "utils.h"
#include <QMessageBox>

utils::utils(generalPluginTypeEnum plugin_type)
	: QDataPoolBasic(this)
	, _pluginType(plugin_type)
{
}

utils::~utils()
{
}

void utils::handleData(QVariant data)
{
}

void utils::getPluginType(generalPluginTypeEnum& plugin_type)
{
	plugin_type = _pluginType;
}

QWidget* utils::getWidgetHandler()
{
	QMessageBox* box = new QMessageBox;
	box->setWindowTitle("Config");
	box->setText(QStringLiteral("lxfs:1290486803@qq.com"));
	return box;
}