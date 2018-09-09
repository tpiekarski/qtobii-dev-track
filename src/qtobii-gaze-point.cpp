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

#include "qtobii-gaze-point.h"

namespace qtobii {

void QTobiiGazePoint::callback(tobii_gaze_point_t const* gazePoint, void* exchange) {
  auto exchangeContainer = static_cast<QTobiiExchangeContainer<tobii_gaze_point_t, QString>*>(exchange);

  if (gazePoint->validity == TOBII_VALIDITY_VALID) {
    exchangeContainer->getData()->send(*gazePoint);
    exchangeContainer->getMessages()->send(QString("X/Y: %1").arg(extract(gazePoint->position_xy)));
  }
}

QString QTobiiGazePoint::extract(const float values[]) {
  return QString("%1/%2").arg(QString::number(static_cast<double>(values[0])), QString::number(static_cast<double>(values[1])));
}

void QTobiiGazePoint::subscribe() {
  emit log("Subscribing to gaze point...");

  m_data = new QTobiiData<tobii_gaze_point_t>(this);
  m_messages = new QTobiiData<QString>(this);
  m_exchangeContainer = new QTobiiExchangeContainer<tobii_gaze_point_t, QString>(m_data, m_messages);

  #ifdef QTOBII_MSVC_QOVERLOAD_WORKAROUND
    connect(m_messages, static_cast<void (QTobiiDataMessenger::*)(QString)>(&QTobiiData<QString>::transmit),
            m_api->getLogger().get(), &QTobiiLogger::data);
  #else
    connect(messages, qOverload<QString>(&QTobiiData<QString>::transmit), api->getLogger(), &QTobiiLogger::data);
  #endif

  m_result = m_api->call(tobii_gaze_point_subscribe(m_api->getDevice(), callback, m_exchangeContainer));

  if (m_result->isError()) {
    emit log("Failed subscribing to gaze point.");
    m_result.reset();
    unsubscribe();
  }

}

void QTobiiGazePoint::unsubscribe() {
  emit log("Unsubscribing from gaze point...");

  if (m_exchangeContainer != nullptr) {

    if (m_data != nullptr) {
      disconnect(m_data);
      delete m_data;
      m_data = nullptr;
    }

    if (m_messages != nullptr) {
      disconnect(m_messages);
      delete m_messages;
      m_messages = nullptr;
    }

    delete m_exchangeContainer;
    m_exchangeContainer = nullptr;
  }

  m_result = m_api->call(tobii_gaze_point_unsubscribe(m_api->getDevice()));

  if (m_result->isError()) {
    emit log("Failed unsubscribing from gaze point");
    m_result.reset();
  }
}

} // namespace qtobii
