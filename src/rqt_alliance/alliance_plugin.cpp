#include "rqt_alliance/alliance_plugin.h"
#include <pluginlib/class_list_macros.h>
#include <QStringList>

PLUGINLIB_DECLARE_CLASS(rqt_alliance, AlliancePlugin,
                        rqt_alliance::AlliancePlugin, rqt_gui_cpp::Plugin)

namespace rqt_alliance
{
AlliancePlugin::AlliancePlugin() : rqt_gui_cpp::Plugin(), widget_(NULL)
{
  // Constructor is called first before initPlugin function, needless to say.

  // give QObjects reasonable names
  setObjectName("AlliancePlugin");
}

void AlliancePlugin::initPlugin(qt_gui_cpp::PluginContext& context)
{
  // access standalone command line arguments
  QStringList argv = context.argv();
  // create QWidget
  widget_ = new QWidget();
  // extend the widget with all attributes and children from UI file
  ui_.setupUi(widget_);
  // add widget to the user interface
  context.addWidget(widget_);
}

void AlliancePlugin::shutdownPlugin()
{
  // unregister all publishers here
}

void AlliancePlugin::saveSettings(qt_gui_cpp::Settings& plugin_settings,
                                  qt_gui_cpp::Settings& instance_settings) const
{
  // instance_settings.setValue(k, v)
}

void AlliancePlugin::restoreSettings(
    const qt_gui_cpp::Settings& plugin_settings,
    const qt_gui_cpp::Settings& instance_settings)
{
  // v = instance_settings.value(k)
}

/*bool hasConfiguration() const
{
  return true;
}

void triggerConfiguration()
{
  // Usually used to open a dialog to offer the user a set of configuration
}*/
} // namespace rqt_alliance
