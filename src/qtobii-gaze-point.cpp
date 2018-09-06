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
#include "qtobii-logger.h"
#include <QThread>

namespace qtobii {

void QTobiiGazePoint::callback(tobii_gaze_point_t const* gazePoint, void* exchange) {
  auto exchangeContainer = static_cast<QTobiiExchangeContainer<tobii_gaze_point_t, QString>*>(exchange);

  exchangeContainer->getData()->send(*gazePoint);
  exchangeContainer->getMessages()->send(QString("X/Y: %1").arg(extract(gazePoint->position_xy)));
}

QString QTobiiGazePoint::extract(const float values[]) {
  return QString("%1/%2").arg(QString::number(static_cast<double>(values[0])), QString::number(static_cast<double>(values[1])));
}

void QTobiiGazePoint::subscribe() {
  emit log("Subscribing to gaze point...");

  data = new QTobiiData<tobii_gaze_point_t>(this);
  messages = new QTobiiData<QString>(this);
  exchangeContainer = new QTobiiExchangeContainer<tobii_gaze_point_t, QString>(data, messages);

  #ifdef QTOBII_MSVC_QOVERLOAD_WORKAROUND
    connect(messages, static_cast<void (QTobiiDataMessenger::*)(QString)>(&QTobiiData<QString>::transmit),
            api->getLogger(), &QTobiiLogger::data);
  #else
    connect(messages, qOverload<QString>(&QTobiiData<QString>::transmit), api->getLogger(), &QTobiiLogger::data);
  #endif

  result = api->call(tobii_gaze_point_subscribe(api->getDevice(), callback, exchangeContainer));

  if (result->isError()) {
    emit log("Failed subscribing to gaze point.");
    delete result;
    result = nullptr;
    unsubscribe();
  }

}

void QTobiiGazePoint::unsubscribe() {
  emit log("Unsubscribing from gaze point...");

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

  result = api->call(tobii_gaze_point_unsubscribe(api->getDevice()));

  if (result->isError()) {
    emit log("Failed unsubscribing from gaze point");

    delete result;
    result = nullptr;
  }
}

} // namespace qtobii
