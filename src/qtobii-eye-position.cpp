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

#include "qtobii-eye-position.h"

namespace qtobii {

void QTobiiEyePosition::callback(tobii_eye_position_normalized_t const* eyePosition, void* exchange) {
  auto exchangeContainer = static_cast<QTobiiExchangeContainer<tobii_eye_position_normalized_t, QString>*>(exchange);

  if (eyePosition->left_validity == TOBII_VALIDITY_VALID) {
    exchangeContainer->getData()->send(*eyePosition);
    exchangeContainer->getMessages()->send(QString("Left eye (X/Y/Z): %1").arg(extract(eyePosition->left_xyz)));
  }

  if (eyePosition->right_validity == TOBII_VALIDITY_VALID) {
    exchangeContainer->getData()->send(*eyePosition);
    exchangeContainer->getMessages()->send(QString("Right eye (X/Y/Z): %1").arg(extract(eyePosition->right_xyz)));
  }
}

QString QTobiiEyePosition::extract(const float values[]) {
  return QString("%1/%2/%3").arg(
        QString::number(static_cast<double>(values[0])),
        QString::number(static_cast<double>(values[1])),
        QString::number(static_cast<double>(values[2])));
}

void QTobiiEyePosition::subscribe() {
  emit log("Subscribing to eye position...");

  m_data = new QTobiiData<tobii_eye_position_normalized_t>(this);
  m_messages = new QTobiiData<QString>(this);
  m_exchangeContainer = new QTobiiExchangeContainer<tobii_eye_position_normalized_t, QString>(m_data, m_messages);

  #ifdef QTOBII_MSVC_QOVERLOAD_WORKAROUND
    connect(m_messages, static_cast<void (QTobiiDataMessenger::*)(QString)>(&QTobiiData<QString>::transmit),
            m_api->getLogger().get(), &QTobiiLogger::data);
  #else
    connect(messages, qOverload<QString>(&QTobiiData<QString>::transmit), api->getLogger(), &QTobiiLogger::data);
  #endif

  m_result = m_api->call(tobii_eye_position_normalized_subscribe(m_api->getDevice(), callback, m_exchangeContainer));

  if (m_result->isError()) {
    emit log("Failed subscribing to eye position.");
    delete m_result;
    m_result = nullptr;
    unsubscribe();
  }

}

void QTobiiEyePosition::unsubscribe() {
  emit log("Unsubscribing from eye position...");

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

  m_result = m_api->call(tobii_eye_position_normalized_unsubscribe(m_api->getDevice()));

  if (m_result->isError()) {
    emit log("Failed unsubscribing from eye position.");

    delete m_result;
    m_result = nullptr;
  }
}

}
