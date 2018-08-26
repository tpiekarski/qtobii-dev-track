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
#include "qtobii-api-exception.h"
#include <algorithm>
#include <QDebug>

namespace qtobii {

QTobiiDevice::QTobiiDevice(QObject *parent)
  : QObject(parent), version(new tobii_version_t), api(nullptr), device(nullptr), url("")
{
  call(tobii_get_api_version(version));
  call(tobii_api_create(&api, nullptr, nullptr));

  char rawURL[256] = { 0 };
  call(tobii_enumerate_local_device_urls(api, deviceReceiver, rawURL));
  call(tobii_device_create(api, rawURL, &device));

  url = QString::fromLatin1(rawURL);

  qDebug() << "Tobii Stream API, Version: " << getVersion();
  qDebug() << "Device URL: " << getUrl();
}

QTobiiDevice::~QTobiiDevice() {
  if (version != nullptr) {
    delete version;
    version = nullptr;
  }

  if (device != nullptr) {
    call(tobii_device_destroy(device));
    device = nullptr;
  }

  if (api != nullptr) {
    call(tobii_api_destroy(api));
    api = nullptr;
  }

  if (!results.empty()) {
#ifndef QT_NO_DEBUG_OUTPUT
    qDebug() << "Result Message Stack:";
    std::for_each(results.begin(), results.end(), [](QTobiiResult *result) {
      qDebug() << " " << result->getMessage();
    });
#endif

    results.clear();
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

    throw QTobiiApiException(lastMessage.toStdString());
  }

  results.append(result);
}

void QTobiiDevice::deviceReceiver(const char* url, void* userData) {
  char* buffer = static_cast<char*>(userData);

  if (*buffer != '\0') {
    return;
  }

  if (strlen(url) < 256) {
    strcpy_s(buffer, sizeof(char) * 256, url);
  }
}

} // namespace qtobii
