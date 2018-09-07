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

#ifndef QTOBIIEYEPOSITIONLCDDISPLAY_H
#define QTOBIIEYEPOSITIONLCDDISPLAY_H

#include "interfaces/qtobii-display.h"
#include "qtobii-dev-track.h"
#include <QObject>
#include <tobii/tobii_streams.h>

namespace qtobii {
class QTobiiEyePositionLCDDisplay
    : public QObject, public QTobiiDisplayInterface<QTobiiDevTrack*, tobii_eye_position_normalized_t>
{

  Q_OBJECT

public:
  explicit QTobiiEyePositionLCDDisplay(QTobiiDevTrack* device, QObject* parent = nullptr)
    : QObject(parent), QTobiiDisplayInterface<QTobiiDevTrack*, tobii_eye_position_normalized_t>(device) {}
  QTobiiEyePositionLCDDisplay(const QTobiiEyePositionLCDDisplay&) = default;
  QTobiiEyePositionLCDDisplay(QTobiiEyePositionLCDDisplay&&) = default;

  virtual void display(tobii_eye_position_normalized_t payload) override;

public slots:
  void displayEyePosition(tobii_eye_position_normalized_t payload);

};
} // namespace qtobii

#endif // QTOBIIEYEPOSITIONLCDDISPLAY_H
