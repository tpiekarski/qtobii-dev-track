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

#include "qtobii-plugin-exception.h"
#include "qtobii-plugin-loader.h"
#include <QFileInfoList>
#include <QPluginLoader>
#include <QDebug>

namespace qtobii {

void QTobiiPluginLoader::load(QDir directory) {
  QFileInfoList pluginFiles = directory.entryInfoList(QDir::NoDotAndDotDot | QDir::Files, QDir::Name);

  if (pluginFiles.empty()) {
    throw QTobiiPluginException(
      QString("No Plugins found in the directory '%1', aborting.").arg(directory.absolutePath()).toStdString()
    );
  }

  foreach(QFileInfo pluginFile, pluginFiles) {
    if (!QLibrary::isLibrary(pluginFile.absoluteFilePath())) {
      continue;
    }

    if (pluginFile.baseName() == "qtobii-gaze-point") {
      gazePointPlugin = loadGazePointPlugin(&pluginFile);
    }

  }
}

QTobiiPlugin<tobii_gaze_point_callback_t, void*>* QTobiiPluginLoader::loadGazePointPlugin(QFileInfo* pluginFile) {
  QPluginLoader pluginLoader(pluginFile->absoluteFilePath());
  QObject* object = pluginLoader.instance();

  if (object == nullptr) {
    QString message = QString("Creating instance from the file '%1' failed, aborting.").arg(pluginFile->fileName());
    qDebug() << message;

    throw QTobiiPluginException(message.toStdString());
  }

  auto plugin = dynamic_cast<QTobiiPlugin<tobii_gaze_point_callback_t, void*> *>(object);

  if (plugin == nullptr) {
    QString message = QString("Casting '%1' to QTobiiPlugin failed, aborting.").arg(pluginFile->baseName());
    qDebug() << message;

    throw QTobiiPluginException(message.toStdString());
  }

  return plugin;
}

}
