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
#include "qtobii-device-exception.h"
#include <QDebug>

namespace qtobii {

QTobiiDevice::QTobiiDevice(QObject *parent) : QObject(parent) {
  version = new tobii_version_t();
  call(tobii_get_api_version(version));
  call(tobii_api_create(&api, nullptr, nullptr));

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

void QTobiiDevice::call(tobii_error_t error) {
  QTobiiResult* result = new QTobiiResult(error);

  if (result->isError()) {
    QString lastMessage(result->getMessage());
    delete result;
    result = nullptr;

    throw QTobiiDeviceException(lastMessage.toStdString());
  }

  results.append(result);
}

} // namespace qtobii
