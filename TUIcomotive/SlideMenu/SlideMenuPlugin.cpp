#include "SlideMenu.h"
#include "SlideMenuPlugin.h"

#include <QtCore/QtPlugin>

SlideMenuPlugin::SlideMenuPlugin(QObject *parent)
	: QObject(parent)
{
	initialized = false;
}

void SlideMenuPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
	if (initialized)
		return;

	initialized = true;
}

bool SlideMenuPlugin::isInitialized() const
{
	return initialized;
}

QWidget *SlideMenuPlugin::createWidget(QWidget *parent)
{
	return new SlideMenu(parent);
}

QString SlideMenuPlugin::name() const
{
	return "SlideMenu";
}

QString SlideMenuPlugin::group() const
{
	return "My Plugins";
}

QIcon SlideMenuPlugin::icon() const
{
	return QIcon();
}

QString SlideMenuPlugin::toolTip() const
{
	return QString();
}

QString SlideMenuPlugin::whatsThis() const
{
	return QString();
}

bool SlideMenuPlugin::isContainer() const
{
	return false;
}

QString SlideMenuPlugin::domXml() const
{
	return "<widget class=\"SlideMenu\" name=\"slideMenu\">\n"
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

QString SlideMenuPlugin::includeFile() const
{
	return "SlideMenu.h";
}
