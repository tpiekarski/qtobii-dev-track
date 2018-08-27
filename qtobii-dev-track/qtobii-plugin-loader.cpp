/*
 * Project:   QTobiiDevTrack - Utility for discovering, testing and developing eye and gaze tracking
 * Github:    https://github.com/tpiekarski/qtobii-dev-track
 * Copyright: (c) 2018 Thomas Piekarski <t.piekarski@deloquencia.de>
 * License:   Mozilla Public License, v. 2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

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
