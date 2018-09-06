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

#include "qtobii-gaze-origin.h"
#include "qtobii-logger.h"
#include <QThread>

namespace qtobii {

void QTobiiGazeOrigin::callback(tobii_gaze_origin_t const* gazeOrigin, void* exchange) {
  auto exchangeContainer = static_cast<QTobiiExchangeContainer<tobii_gaze_origin_t, QString>*>(exchange);

  if (gazeOrigin->left_validity == TOBII_VALIDITY_VALID) {
    exchangeContainer->getData()->send(*gazeOrigin);
    exchangeContainer->getMessages()->send(QString("Left eye (X/Y/Z): %1").arg(extract(gazeOrigin->left_xyz)));
  }

  if (gazeOrigin->right_validity == TOBII_VALIDITY_VALID) {
    exchangeContainer->getData()->send(*gazeOrigin);
    exchangeContainer->getMessages()->send(QString("Right eye (X/Y/Z): %1").arg(extract(gazeOrigin->right_xyz)));
  }
}

QString QTobiiGazeOrigin::extract(const float values[]) {
  // todo: perform static_cast of values before passing them to number
  return QString("%1/%2/%3").arg(QString::number(values[0]), QString::number(values[1]), QString::number(values[2]));
}

void QTobiiGazeOrigin::subscribe() {
  emit log("Subscribing to gaze origin...");

  data = new QTobiiData<tobii_gaze_origin_t>(this);
  messages = new QTobiiData<QString>(this);
  exchangeContainer = new QTobiiExchangeContainer<tobii_gaze_origin_t, QString>(data, messages);

  #ifdef QTOBII_MSVC_QOVERLOAD_WORKAROUND
    connect(messages, static_cast<void (QTobiiDataMessenger::*)(QString)>(&QTobiiData<QString>::transmit),
            api->getLogger(), &QTobiiLogger::data);
  #else
    connect(messages, qOverload<QString>(&QTobiiData<QString>::transmit), api->getLogger(), &QTobiiLogger::data);
  #endif

  result = api->call(tobii_gaze_origin_subscribe(api->getDevice(), callback, exchangeContainer));

  if (result->isError()) {
    emit log("Failed subscribing to gaze origin.");
    delete result;
    result = nullptr;
    unsubscribe();
  }
}

void QTobiiGazeOrigin::unsubscribe() {
  emit (log("Unsubscribing from gaze origin..."));

  if (exchangeContainer != nullptr) {

    if (data != nullptr) {
      disconnect(data);
      delete data;
      data = nullptr;
    }

    if (messages != nullptr) {
      disconnect(messages);
      delete messages;
      messages = nullptr;
    }

    delete exchangeContainer;
    exchangeContainer = nullptr;
  }

  result = api->call(tobii_gaze_origin_unsubscribe(api->getDevice()));

  if (result->isError()) {
    emit log("Failed unsubscribing from gaze origin");

    delete result;
    result = nullptr;
  }
}

} // namespace qtobii

