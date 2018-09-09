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
  explicit QTobiiGazeOrigin(shared_ptr<QTobiiApi> api, QObject* parent = nullptr)
    : QObject(parent),
      QTobiiSubscriptionInterface(api),
      m_exchangeContainer(nullptr),
      m_data(nullptr),
      m_messages(nullptr) {}

  QTobiiGazeOrigin(const QTobiiGazeOrigin&) = default;
  QTobiiGazeOrigin(QTobiiGazeOrigin&&) = default;

  virtual void subscribe() override;
  virtual void unsubscribe() override;

  QTobiiData<tobii_gaze_origin_t>* getData() { return m_data; }

signals:
  void log(QString message);

private:
  static void callback(tobii_gaze_origin_t const* gazeOrigin, void* exchange);
  static QString extract(const float values[]);

  QTobiiExchangeContainer<tobii_gaze_origin_t, QString>* m_exchangeContainer;
  QTobiiData<tobii_gaze_origin_t>* m_data;
  QTobiiData<QString>* m_messages;

};
} // namespace qtobii

#endif // QTOBIIGAZEORIGIN_H
