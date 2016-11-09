#include "StackSlide.h"
#include "StackSlidePlugin.h"

#include <QtCore/QtPlugin>

StackSlidePlugin::StackSlidePlugin(QObject *parent)
	: QObject(parent)
{
	initialized = false;
}

void StackSlidePlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
	if (initialized)
		return;

	initialized = true;
}

bool StackSlidePlugin::isInitialized() const
{
	return initialized;
}

QWidget *StackSlidePlugin::createWidget(QWidget *parent)
{
	return new StackSlide(parent);
}

QString StackSlidePlugin::name() const
{
	return "StackSlide";
}

QString StackSlidePlugin::group() const
{
	return "My Plugins";
}

QIcon StackSlidePlugin::icon() const
{
	return QIcon();
}

QString StackSlidePlugin::toolTip() const
{
	return QString();
}

QString StackSlidePlugin::whatsThis() const
{
	return QString();
}

bool StackSlidePlugin::isContainer() const
{
	return false;
}

QString StackSlidePlugin::domXml() const
{
	return "<widget class=\"StackSlide\" name=\"stackSlide\">\n"
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

QString StackSlidePlugin::includeFile() const
{
	return "StackSlide.h";
}
