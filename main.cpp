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
#include "qtobii-device-exception.h"
#include <QApplication>
#include <QDebug>
#include <QMessageBox>

using namespace qtobii;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  int result = 0;
  QTobiiDevTrack* devTrack = new QTobiiDevTrack();
  QTobiiDevice* device = nullptr;

  try {
    device = new QTobiiDevice(devTrack);
    devTrack->show();
    result = app.exec();
  } catch (QTobiiDeviceException& e) {
    QString lastMessage(QString::fromStdString(e.what()));
    qDebug() << "Last Message from device: " << lastMessage;
    QMessageBox::critical(devTrack, "Error", lastMessage, QMessageBox::Ok);
    result = 2;
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
