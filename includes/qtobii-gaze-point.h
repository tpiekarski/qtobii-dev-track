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

#ifndef QTOBIIGAZEPOINT_H
#define QTOBIIGAZEPOINT_H

#include "interfaces/qtobii-subscription.h"
#include "qtobii-exchange-container.h"
#include "qtobii-data.h"
#include "qtobii-dev-track.h"
#include "qtobii-result.h"
#include <QObject>
#include <QPair>
#include <QString>
#include <QVector>
#include <tobii/tobii.h>
#include <tobii/tobii_streams.h>

namespace qtobii {
class QTobiiGazePoint : public QObject, public QTobiiSubscriptionInterface {

  Q_OBJECT

public:
  QTobiiGazePoint(QTobiiApi* api)
    : QTobiiSubscriptionInterface(api),
        exchangeContainer(nullptr),
        data(nullptr),
        messages(nullptr),
        result(nullptr),
        tracking(true)
    { /* Nothing further to construct. */ }

  virtual void subscribe() override;
  virtual void unsubscribe() override;

  QTobiiData<tobii_gaze_point_t>* getData() { return data; }

signals:
  void log(QString message);

private:
  static void callback(tobii_gaze_point_t const* gazePoint, void* exchange);

  QTobiiExchangeContainer<tobii_gaze_point_t, QString>* exchangeContainer;
  QTobiiData<tobii_gaze_point_t>* data;
  QTobiiData<QString>* messages;
  QTobiiResult* result;
  bool tracking;

};
} // namespace qtobii

#endif // QTOBIIGAZEPOINT_H
