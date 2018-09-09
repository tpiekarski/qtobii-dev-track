/*
 * Project:   QTobiiDevTrack - Utility for discovering, testing and developing head and gaze tracking
 * Github:    https://github.com/tpiekarski/qtobii-dev-track
 * Copyright: (c) 2018 Thomas Piekarski <t.piekarski@deloquencia.de>
 * License:   Mozilla Public License, v. 2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#include "qtobii-head-position.h"

namespace qtobii {

void QTobiiHeadPosition::callback(tobii_head_pose_t const* headPosition, void* exchange) {
  auto exchangeContainer = static_cast<QTobiiExchangeContainer<tobii_head_pose_t, QString>*>(exchange);

  if (headPosition->position_validity == TOBII_VALIDITY_VALID) {
    exchangeContainer->getData()->send(*headPosition);
    exchangeContainer->getMessages()->send(QString("Head position (X/Y/Z): %1").arg(extract(headPosition->position_xyz)));
  }

  if (
      headPosition->rotation_validity_xyz[0] == TOBII_VALIDITY_VALID
      && headPosition->rotation_validity_xyz[1] == TOBII_VALIDITY_VALID
      && headPosition->rotation_validity_xyz[2] == TOBII_VALIDITY_VALID
  ) {
    exchangeContainer->getData()->send(*headPosition);
    exchangeContainer->getMessages()->send(QString("Head rotation (X/Y/Z): %1").arg(extract(headPosition->rotation_xyz)));
  }
}

QString QTobiiHeadPosition::extract(const float values[]) {
  return QString("%1/%2/%3").arg(
        QString::number(static_cast<double>(values[0])),
        QString::number(static_cast<double>(values[1])),
        QString::number(static_cast<double>(values[2])));
}

void QTobiiHeadPosition::subscribe() {
  emit log("Subscribing to head position...");

  m_data = new QTobiiData<tobii_head_pose_t>(this);
  m_messages = new QTobiiData<QString>(this);
  m_exchangeContainer = new QTobiiExchangeContainer<tobii_head_pose_t, QString>(m_data, m_messages);

  #ifdef QTOBII_MSVC_QOVERLOAD_WORKAROUND
    connect(m_messages, static_cast<void (QTobiiDataMessenger::*)(QString)>(&QTobiiData<QString>::transmit),
            m_api->getLogger().get(), &QTobiiLogger::data);
  #else
    connect(messages, qOverload<QString>(&QTobiiData<QString>::transmit), api->getLogger(), &QTobiiLogger::data);
  #endif

  m_result = m_api->call(tobii_head_pose_subscribe(m_api->getDevice(), callback, m_exchangeContainer));

  if (m_result->isError()) {
    emit log("Failed subscribing to head position.");
    delete m_result;
    m_result = nullptr;
    unsubscribe();
  }

}

void QTobiiHeadPosition::unsubscribe() {
  emit log("Unsubscribing from head position...");

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

  m_result = m_api->call(tobii_head_pose_unsubscribe(m_api->getDevice()));

  if (m_result->isError()) {
    emit log("Failed unsubscribing from head position.");

    delete m_result;
    m_result = nullptr;
  }
}

}
