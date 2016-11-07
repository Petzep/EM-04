#include "QtPieMenu.h"
#include "QtPieMenuPlugin.h"

#include <QtCore/QtPlugin>

QtPieMenuPlugin::QtPieMenuPlugin(QObject *parent)
	: QObject(parent)
{
	initialized = false;
}

void QtPieMenuPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
	if (initialized)
		return;

	initialized = true;
}

bool QtPieMenuPlugin::isInitialized() const
{
	return initialized;
}

QWidget *QtPieMenuPlugin::createWidget(QWidget *parent)
{
	return new QtPieMenu(parent);
}

QString QtPieMenuPlugin::name() const
{
	return "QtPieMenu";
}

QString QtPieMenuPlugin::group() const
{
	return "My Plugins";
}

QIcon QtPieMenuPlugin::icon() const
{
	return QIcon();
}

QString QtPieMenuPlugin::toolTip() const
{
	return QString("Main menu of the TUInterface");
}

QString QtPieMenuPlugin::whatsThis() const
{
	return QString("Desgined by Nephtaly Ancieta");
}

bool QtPieMenuPlugin::isContainer() const
{
	return false;
}

QString QtPieMenuPlugin::domXml() const
{
	return "<widget class=\"QtPieMenu\" name=\"qtPieMenu\">\n"
		" <property name=\"geometry\">\n"
		"  <rect>\n"
		"   <x>0</x>\n"
		"   <y>0</y>\n"
		"   <width>100</width>\n"
		"   <height>100</height>\n"
		"  </rect>\n"
		" </property>\n"
		"</widget>\n";
}

QString QtPieMenuPlugin::includeFile() const
{
	return "QtPieMenu.h";
}
