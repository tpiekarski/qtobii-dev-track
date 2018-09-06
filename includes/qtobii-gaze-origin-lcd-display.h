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

#ifndef QTOBIIGAZEORIGINLCDDISPLAY_H
#define QTOBIIGAZEORIGINLCDDISPLAY_H

#include "interfaces/qtobii-display.h"
#include "qtobii-dev-track.h"
#include <QObject>
#include <tobii/tobii_streams.h>

namespace qtobii {
class QTobiiGazeOriginLCDDisplay : public QObject, public QTobiiDisplayInterface<QTobiiDevTrack*, tobii_gaze_origin_t> {

  Q_OBJECT

public:
  explicit QTobiiGazeOriginLCDDisplay(QTobiiDevTrack* device, QObject* parent = nullptr)
    : QObject(parent), QTobiiDisplayInterface<QTobiiDevTrack*, tobii_gaze_origin_t>(device) {}

  virtual void display(tobii_gaze_origin_t payload) override;

public slots:
  void displayGazeOrigin(tobii_gaze_origin_t payload);

};
} // namespace qtobii

#endif // QTOBIIGAZEORIGINLCDDISPLAY_H
