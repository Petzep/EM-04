#include "CustomClock.h"
#include "CustomClockPlugin.h"

#include <QtCore/QtPlugin>

CustomClockPlugin::CustomClockPlugin(QObject *parent)
	: QObject(parent)
{
	initialized = false;
}

void CustomClockPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
	if (initialized)
		return;

	initialized = true;
}

bool CustomClockPlugin::isInitialized() const
{
	return initialized;
}

QWidget *CustomClockPlugin::createWidget(QWidget *parent)
{
	return new CustomClock(parent);
}

QString CustomClockPlugin::name() const
{
	return "CustomClock";
}

QString CustomClockPlugin::group() const
{
	return "My Plugins";
}

QIcon CustomClockPlugin::icon() const
{
	return QIcon();
}

QString CustomClockPlugin::toolTip() const
{
	return QString("Custom clock test");
}

QString CustomClockPlugin::whatsThis() const
{
	return QString("Desgined by Nephtaly Ancieta");
}

bool CustomClockPlugin::isContainer() const
{
	return false;
}

QString CustomClockPlugin::domXml() const
{
	return "<widget class=\"CustomClock\" name=\"customClock\">\n"
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

QString CustomClockPlugin::includeFile() const
{
	return "CustomClock.h";
}
