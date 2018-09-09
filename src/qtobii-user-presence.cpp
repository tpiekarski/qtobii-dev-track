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

#include "qtobii-user-presence.h"
#include "qtobii-logger.h"
#include <QThread>

namespace qtobii {

void QTobiiUserPresence::callback(tobii_user_presence_status_t userPresence, int64_t timestamp, void* exchange) {
  auto exchangeContainer = static_cast<QTobiiExchangeContainer<tobii_user_presence_status_t, QString>*>(exchange);

  exchangeContainer->getData()->send(userPresence);
  exchangeContainer->getMessages()->send(QString("User Presence: %1, Timestamp: %2").arg(
                                           QString::number(userPresence), QString::number(timestamp)));
}

void QTobiiUserPresence::subscribe() {
  emit log("Subscribing to user presence...");

  m_data = new QTobiiData<tobii_user_presence_status_t>(this);
  m_messages = new QTobiiData<QString>(this);
  m_exchangeContainer = new QTobiiExchangeContainer<tobii_user_presence_status_t, QString>(m_data, m_messages);

  #ifdef QTOBII_MSVC_QOVERLOAD_WORKAROUND
    connect(m_messages, static_cast<void (QTobiiDataMessenger::*)(QString)>(&QTobiiData<QString>::transmit),
            m_api->getLogger().get(), &QTobiiLogger::data);
  #else
    connect(messages, qOverload<QString>(&QTobiiData<QString>::transmit), api->getLogger(), &QTobiiLogger::data);
  #endif

  m_result = m_api->call(tobii_user_presence_subscribe(m_api->getDevice(), callback, m_exchangeContainer));

  if (m_result->isError()) {
    emit log("Failed subscribing to user presence.");
    delete m_result;
    m_result = nullptr;
    unsubscribe();
  }

}

void QTobiiUserPresence::unsubscribe() {
  emit log("Unsubscribing from user presence...");

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

  m_result = m_api->call(tobii_user_presence_unsubscribe(m_api->getDevice()));

  if (m_result->isError()) {
    emit log("Failed unsubscribing from user presence");

    delete m_result;
    m_result = nullptr;
  }
}

} // namespace qtobii
