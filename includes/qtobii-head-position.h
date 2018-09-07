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

#ifndef QTOBIIHEADPOSITION_H
#define QTOBIIHEADPOSITION_H

#include "interfaces/qtobii-subscription.h"
#include "qtobii-exchange-container.h"
#include "qtobii-data.h"
#include <QObject>
#include <QString>
#include <tobii/tobii.h>
#include <tobii/tobii_streams.h>

namespace qtobii {
class QTobiiHeadPosition : public QObject, public QTobiiSubscriptionInterface {

  Q_OBJECT

public:
  explicit QTobiiHeadPosition(QTobiiApi* api, QObject* parent = nullptr)
    : QObject(parent), QTobiiSubscriptionInterface(api),
      m_exchangeContainer(nullptr),
      m_data(nullptr),
      m_messages(nullptr) {}

  QTobiiHeadPosition(const QTobiiHeadPosition&) = default;
  QTobiiHeadPosition(QTobiiHeadPosition&&) = default;

  virtual void subscribe() override;
  virtual void unsubscribe() override;

  QTobiiData<tobii_head_pose_t>* getData() { return m_data; }

signals:
  void log(QString message);

private:
  static void callback(tobii_head_pose_t const* headPosition, void* exchange);
  static QString extract(const float values[]);

  QTobiiExchangeContainer<tobii_head_pose_t, QString>* m_exchangeContainer;
  QTobiiData<tobii_head_pose_t>* m_data;
  QTobiiData<QString>* m_messages;

};
} // namespace qtobii

#endif // QTOBIIHEADPOSITION_H
