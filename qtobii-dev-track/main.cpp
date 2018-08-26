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

#include "qtobii-dev-track.h"
#include "qtobii-device.h"
#include "qtobii-api-exception.h"
#include "../qtobii-plugin-interface/qtobii-plugin-interface.h"
#include "qtobii-plugin-loader.h"
#include <QApplication>
#include <QDebug>
#include <QMessageBox>

using namespace qtobii;

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);
  int result = 0;
  QTobiiDevTrack* devTrack = nullptr;
  QTobiiDevice* device = nullptr;

  // --- plugin development ground zero
  if (argc == 2) {
    QTobiiPluginLoader* pluginLoader = nullptr;
    pluginLoader = new QTobiiPluginLoader();
    QFileInfo* testPlugin = new QFileInfo(QString::fromLatin1(argv[1]));
    qtobii::QTobiiPlugin<tobii_gaze_point_callback_t, void*>* plugin = pluginLoader->loadGazePointPlugin(testPlugin);
    qDebug() << plugin->getDescription();
  }
  // ---

  try {
    devTrack = new QTobiiDevTrack();
    device = new QTobiiDevice(devTrack);
    devTrack->show();

    result = app.exec();
  } catch (QTobiiApiException& e) {
    QString lastMessage(QString::fromStdString(e.what()));
    qDebug() << "Last Message from API: " << lastMessage;
    QMessageBox::critical(devTrack, "Error", lastMessage, QMessageBox::Ok);

    result = 2;
  } catch (std::exception& e) {
    qDebug() << QString::fromLatin1(e.what());

    result = 3;
  }

  if (device != nullptr) {
    if (device->getLastResult()->isError()) {
      result = 1;
    }

    delete device;
    device = nullptr;
  }

  if (devTrack != nullptr) {
    delete devTrack;
    devTrack = nullptr;
  }

  return result;
}
