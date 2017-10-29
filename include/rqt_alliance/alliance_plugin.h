#ifndef RQT_ALLIANCE_PLUGIN_H
#define RQT_ALLIANCE_PLUGIN_H

#include <rqt_gui_cpp/plugin.h>
#include <rqt_alliance/ui_alliance_monitor_widget.h>
#include <rqt_multiplot/MultiplotConfig.h>
#include <QWidget>

namespace rqt_alliance
{

class AlliancePlugin
  : public rqt_gui_cpp::Plugin
{
  Q_OBJECT
public:
  AlliancePlugin();
  virtual void initPlugin(qt_gui_cpp::PluginContext& context);
  virtual void shutdownPlugin();
  virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings,
      qt_gui_cpp::Settings& instance_settings) const;
  virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings,
      const qt_gui_cpp::Settings& instance_settings);

  // Comment in to signal that the plugin has a way to configure it
  // bool hasConfiguration() const;
  // void triggerConfiguration();
private:
  Ui::AllianceMonitorWidget ui_;
  QWidget* widget_;
  rqt_multiplot::MultiplotConfig* config_;
};
}
#endif  // RQT_ALLIANCE_PLUGIN_H
