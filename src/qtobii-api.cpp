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

#include "qtobii-api.h"
#include "qtobii-api-exception.h"
#include <algorithm>
#include <QDebug>

namespace qtobii {

QTobiiApi::QTobiiApi(QObject *parent, QTobiiLogger* logger)
  : QObject(parent), logger(logger), version(new tobii_version_t), api(nullptr), device(nullptr), url("")
{
  setup(tobii_get_api_version(version));
  setup(tobii_api_create(&api, nullptr, nullptr));
  setup(tobii_enumerate_local_device_urls(api, deviceReceiver, &url));
  setup(tobii_device_create(api, url.toLatin1(), &device));

  logger->log(QString("Tobii Stream API, Version: %1").arg(getVersion()));
  logger->log(QString("Device URL: %1").arg(getUrl()));
}

QTobiiApi::~QTobiiApi() {
  if (version != nullptr) {
    delete version;
    version = nullptr;
  }

  if (device != nullptr) {
    setup(tobii_device_destroy(device));
    device = nullptr;
  }

  if (api != nullptr) {
    setup(tobii_api_destroy(api));
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

QString QTobiiApi::getVersion() {
  return QString("%1.%2.%3.%4")
      .arg(QString::number(version->major))
      .arg(QString::number(version->minor))
      .arg(QString::number(version->revision))
      .arg(QString::number(version->build));
}

QTobiiResult* QTobiiApi::call(tobii_error_t error) {
  return new QTobiiResult(error);
}

void QTobiiApi::setup(tobii_error_t error) {
  QTobiiResult* result = new QTobiiResult(error);

  if (result->isError()) {
    QString lastMessage(result->getMessage());
    delete result;
    result = nullptr;

    throw QTobiiApiException(lastMessage.toStdString());
  }

  results.append(result);
}

void QTobiiApi::deviceReceiver(const char* url, void* data) {
  auto buffer = static_cast<QString*>(data);
  if (!buffer->isEmpty()) {
    buffer->clear();
  }

  buffer->append(url);
}

} // namespace qtobii
