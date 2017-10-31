#include <pluginlib/class_list_macros.h>
#include <QFileInfo>
#include <QStringList>
#include "rqt_alliance/alliance_plugin.h"
#include <rqt_multiplot/PlotWidget.h>
#include <utilities/motivation_plot_generator.h>

PLUGINLIB_DECLARE_CLASS(rqt_alliance, AlliancePlugin,
                        rqt_alliance::AlliancePlugin, rqt_gui_cpp::Plugin)

namespace rqt_alliance
{
AlliancePlugin::AlliancePlugin()
    : rqt_gui_cpp::Plugin(), widget_(NULL),
      config_(new rqt_multiplot::MultiplotConfig(this)),
      ui_(new Ui::AllianceMonitorWidget())
{
  setObjectName("AlliancePlugin");
}

AlliancePlugin::~AlliancePlugin()
{
  if (ui_)
  {
    delete ui_;
    ui_ = NULL;
  }
}

void AlliancePlugin::initPlugin(qt_gui_cpp::PluginContext& context)
{
  // access standalone command line arguments
  QStringList argv = context.argv();
  // create QWidget
  widget_ = new QWidget();
  // extend the widget with all attributes and children from UI file
  ui_->setupUi(widget_);
  ui_->plotTableWidget->setConfig(config_->getTableConfig());
  ui_->robotComboBox->addItem("/robot1");
  ui_->robotComboBox->addItem("/robot2");
  ui_->robotComboBox->addItem("/robot3");
  ui_->robotComboBox->addItem("/robot4");
  ui_->robotComboBox->addItem("/robot5");
  ui_->robotComboBox->connect(ui_->robotComboBox,
                              SIGNAL(currentIndexChanged(const QString&)), this,
                              SLOT(updateRobot(const QString&)));
  ui_->taskComboBox->addItem("border_protection");
  ui_->taskComboBox->addItem("report");
  ui_->taskComboBox->addItem("wander");
  ui_->robotComboBox->connect(ui_->taskComboBox,
                              SIGNAL(currentIndexChanged(const QString&)), this,
                              SLOT(updateTask(const QString&)));
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

void AlliancePlugin::updateRobot(const QString& robot_id)
{
  ui_->plotTableWidget->pausePlots();
  ui_->plotTableWidget->clearPlots();
  if (robot_id.isEmpty())
  {
    config_->reset();
    return;
  }
  QString file_path(QString::fromStdString(
      utilities::MotivationPlotConfigGenerator::getFilename(
          robot_id.toStdString())));
  if (loadConfig(file_path))
  {
    ROS_INFO_STREAM("Loaded configuration from [" << file_path.toStdString()
                                                  << "]");
  }
  ui_->plotTableWidget->runPlots();
}

void AlliancePlugin::updateTask(const QString& task_id)
{
  ui_->plotTableWidget->pausePlots();
  ui_->plotTableWidget->clearPlots();
  if (task_id.isEmpty())
  {
    config_->reset();
    return;
  }
  QString robot_id(ui_->robotComboBox->currentText());
  QString file_path(QString::fromStdString(
      utilities::MotivationPlotConfigGenerator::getFilename(
          robot_id.toStdString(), task_id.toStdString())));
  if (loadConfig(file_path))
  {
    ROS_INFO_STREAM("Loaded configuration from [" << file_path.toStdString()
                                                  << "]");
  }
  ui_->plotTableWidget->runPlots();
}

bool AlliancePlugin::loadConfig(const QString& file_path)
{
  if (config_)
  {
    if (!file_path.isEmpty())
    {
      QFileInfo file_info(file_path);
      if (file_info.isReadable())
      {
        QSettings settings(file_path, rqt_multiplot::XmlSettings::format);
        if (settings.status() == QSettings::NoError)
        {
          settings.beginGroup("rqt_multiplot");
          config_->load(settings);
          settings.endGroup();
          return true;
        }
      }
    }
  }
  return false;
}
}
