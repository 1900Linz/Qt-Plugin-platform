#include "homeWidget.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>

 HomeWidget* inst = nullptr;

HomeWidget::HomeWidget(QWidget* parent)
	:QWidget(parent)
	, open(new QPushButton(QStringLiteral("打开")))
{
	QHBoxLayout lay(this);

	lay.addWidget(open);
	connect(open, &QPushButton::clicked, this,&HomeWidget::BtnThing_openFile);
}
//
//QWidget* homeWidget::instance()
//{
//	if (!inst)
//		inst = new homeWidget;
//
//	return inst;
//}

void HomeWidget::BtnThing_openFile()
{
	auto str = QFileDialog::getOpenFileName(this, QStringLiteral("选择组件"), "./", "库文件(*.dll)");

	emit signNewSignal(str);
}
