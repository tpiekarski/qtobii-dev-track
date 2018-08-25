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

#include "qtobii-device.h"
#include <QDebug>

namespace qtobii {

QTobiiDevice::QTobiiDevice(QObject *parent) : QObject(parent) {
  version = new tobii_version_t();
  results.append(new QTobiiResult(tobii_get_api_version(version)));
  qDebug() << "Tobii Stream API, Version: " << getVersion();
}

QTobiiDevice::~QTobiiDevice() {
  if (version != nullptr) {
    delete version;
    version = nullptr;
  }
}

QString QTobiiDevice::getVersion() {
  return QString("%1.%2.%3.%4")
      .arg(QString::number(version->major))
      .arg(QString::number(version->minor))
      .arg(QString::number(version->revision))
      .arg(QString::number(version->build));
}

} // namespace qtobii
