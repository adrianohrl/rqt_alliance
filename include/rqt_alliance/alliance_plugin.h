#ifndef _RQT_ALLIANCE_PLUGIN_H_
#define _RQT_ALLIANCE_PLUGIN_H_

#include <QWidget>
#include <rqt_alliance/ui_alliance_monitor_widget.h>
#include <rqt_gui_cpp/plugin.h>
#include <rqt_multiplot/MultiplotConfig.h>
#include <rqt_multiplot/XmlSettings.h>

namespace rqt_alliance
{
class AlliancePlugin
  : public rqt_gui_cpp::Plugin
{
  Q_OBJECT
public:
  AlliancePlugin();
  virtual ~AlliancePlugin();
  virtual void initPlugin(qt_gui_cpp::PluginContext& context);
  virtual void shutdownPlugin();
  virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings,
      qt_gui_cpp::Settings& instance_settings) const;
  virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings,
      const qt_gui_cpp::Settings& instance_settings);

public slots:
  void updateRobot(const QString& robot_id);
  void updateTask(const QString &task_id);

private:
  Ui::AllianceMonitorWidget* ui_;
  QWidget* widget_;
  rqt_multiplot::MultiplotConfig* config_;
  bool loadConfig(const QString& file_path);
};
}
#endif  // _RQT_ALLIANCE_PLUGIN_H_
