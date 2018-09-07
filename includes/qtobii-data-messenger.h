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

#ifndef QTOBIIDATAMESSENGER_H
#define QTOBIIDATAMESSENGER_H

#include <QObject>
#include <tobii/tobii_streams.h>

namespace qtobii {
class QTobiiDataMessenger : public QObject {

  Q_OBJECT

public:
  explicit QTobiiDataMessenger(QObject* parent = nullptr) : QObject(parent) {}
  QTobiiDataMessenger(const QTobiiDataMessenger&) = default;
  QTobiiDataMessenger(QTobiiDataMessenger&&) = default;
  ~QTobiiDataMessenger() { /* Defined to make sure all destructors along inheritance will be called. */ }

signals:
  void transmit(QString payload);
  void transmit(tobii_eye_position_normalized_t payload);
  void transmit(tobii_gaze_origin_t payload);
  void transmit(tobii_gaze_point_t payload);
  void transmit(tobii_head_pose_t payload);

};
} // namespace tobii

#endif // QTOBIIDATA_H
