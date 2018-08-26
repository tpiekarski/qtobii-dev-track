#include "qtobii-plugin-loader.h"
#include <QPluginLoader>
#include <QDebug>

namespace qtobii {

QTobiiPlugin<tobii_gaze_point_callback_t, void*>* QTobiiPluginLoader::loadGazePointPlugin(QFileInfo* pluginFile) {
  QPluginLoader pluginLoader(pluginFile->absoluteFilePath());
  QObject* object = pluginLoader.instance();

  if (object == nullptr) {
    qDebug() << QString("Creating instance failed of (%1) failed, aborting.").arg(pluginFile->fileName());
    // todo: throw exception
  }

  auto plugin = dynamic_cast<QTobiiPlugin<tobii_gaze_point_callback_t, void*> *>(object);

  if (plugin == nullptr) {
    qDebug() << "Casting to QTobiiPlugin failed, aborting.";
    // todo: throw exception
  }

  return plugin;
}

}
