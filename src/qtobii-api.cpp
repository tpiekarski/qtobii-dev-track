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

QTobiiApi::QTobiiApi(std::shared_ptr<QTobiiLogger> logger, QObject* parent)
  : QObject(parent), m_api(nullptr), m_device(nullptr), m_version(new tobii_version_t()), m_logger(logger), m_url("")
{
  setup(tobii_get_api_version(m_version));
  setup(tobii_api_create(&m_api, nullptr, nullptr));
  setup(tobii_enumerate_local_device_urls(m_api, deviceReceiver, &m_url));
  setup(tobii_device_create(m_api, m_url.toLatin1(), &m_device));

  logger->log(QString("Tobii Stream API, Version: %1").arg(getVersion()));
  logger->log(QString("Device URL: %1").arg(getUrl()));
}

QTobiiApi::~QTobiiApi() {
  if (m_version != nullptr) {
    delete m_version;
    m_version = nullptr;
  }

  if (m_device != nullptr) {
    setup(tobii_device_destroy(m_device));
    m_device = nullptr;
  }

  if (m_api != nullptr) {
    setup(tobii_api_destroy(m_api));
    m_api = nullptr;
  }

  if (!m_results.empty()) {
    #ifndef QT_NO_DEBUG_OUTPUT
      qDebug() << "Result Message Stack:";
      std::for_each(m_results.begin(), m_results.end(), [](QTobiiResult* result) {
        qDebug() << " " << result->getMessage();
      });
    #endif

    m_results.clear();
  }
}

QString QTobiiApi::getVersion() {
  return QString("%1.%2.%3.%4").arg(
    QString::number(m_version->major),
    QString::number(m_version->minor),
    QString::number(m_version->revision),
    QString::number(m_version->build));
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

  m_results.append(result);
}

void QTobiiApi::deviceReceiver(const char* url, void* data) {
  auto buffer = static_cast<QString*>(data);
  if (!buffer->isEmpty()) {
    buffer->clear();
  }

  buffer->append(url);
}

} // namespace qtobii
