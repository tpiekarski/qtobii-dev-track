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

#ifndef QTOBIIGAZEORIGIN_H
#define QTOBIIGAZEORIGIN_H

#include "interfaces/qtobii-subscription.h"
#include "qtobii-exchange-container.h"
#include "qtobii-data.h"
#include <QObject>
#include <QString>
#include <tobii/tobii.h>
#include <tobii/tobii_streams.h>

namespace qtobii {
class QTobiiGazeOrigin : public QObject, public QTobiiSubscriptionInterface {

  Q_OBJECT

public:
  // todo: pass parent to qobject
  explicit QTobiiGazeOrigin(QTobiiApi* api)
    : QTobiiSubscriptionInterface(api) {}

  virtual void subscribe() override;
  virtual void unsubscribe() override;

  QTobiiData<tobii_gaze_origin_t>* getData() { return data; }

signals:
  void log(QString message);

private:
  static void callback(tobii_gaze_origin_t const* gazeOrigin, void* exchange);
  static QString extract(const float values[]);

  QTobiiExchangeContainer<tobii_gaze_origin_t, QString>* exchangeContainer;
  QTobiiData<tobii_gaze_origin_t>* data;
  QTobiiData<QString>* messages;

};
} // namespace qtobii

#endif // QTOBIIGAZEORIGIN_H
