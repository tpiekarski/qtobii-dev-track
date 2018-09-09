/*
 * Project:   QTobiiDevTrack - Utility for discovering, testing and developing Head and gaze tracking
 * Github:    https://github.com/tpiekarski/qtobii-dev-track
 * Copyright: (c) 2018 Thomas Piekarski <t.piekarski@deloquencia.de>
 * License:   Mozilla Public License, v. 2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#ifndef QTOBIIHEADPOSITIONLCDDISPLAY_H
#define QTOBIIHEADPOSITIONLCDDISPLAY_H

#include "interfaces/qtobii-display.h"
#include "qtobii-dev-track.h"
#include <memory>
#include <QObject>
#include <tobii/tobii_streams.h>

namespace qtobii {

using std::shared_ptr;

class QTobiiHeadPositionLCDDisplay : public QObject, public QTobiiDisplayInterface<shared_ptr<QTobiiDevTrack>, tobii_head_pose_t> {

  Q_OBJECT

public:
  explicit QTobiiHeadPositionLCDDisplay(shared_ptr<QTobiiDevTrack> device, QObject* parent = nullptr)
    : QObject(parent), QTobiiDisplayInterface<shared_ptr<QTobiiDevTrack>, tobii_head_pose_t>(device) {}
  QTobiiHeadPositionLCDDisplay(const QTobiiHeadPositionLCDDisplay&) = default;
  QTobiiHeadPositionLCDDisplay(QTobiiHeadPositionLCDDisplay&&) = default;

  virtual void display(const tobii_head_pose_t& payload) override;

public slots:
  void displayHeadPosition(const tobii_head_pose_t& payload);

};
} // namespace qtobii

#endif // QTOBIIHEADPOSITIONLCDDISPLAY_H
