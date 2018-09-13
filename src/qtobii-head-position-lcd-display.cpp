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

#include "qtobii-head-position-lcd-display.h"

namespace qtobii {

void QTobiiHeadPositionLCDDisplay::display(const tobii_head_pose_t& payload) {
  m_device->getHeadPositionXValue()->display(static_cast<double>(payload.position_xyz[QTobiiDevTrack::X]));
  m_device->getHeadPositionYValue()->display(static_cast<double>(payload.position_xyz[QTobiiDevTrack::Y]));
  m_device->getHeadPositionZValue()->display(static_cast<double>(payload.position_xyz[QTobiiDevTrack::Z]));
  m_device->getHeadRotationXValue()->display(static_cast<double>(payload.rotation_xyz[QTobiiDevTrack::X]));
  m_device->getHeadRotationYValue()->display(static_cast<double>(payload.rotation_xyz[QTobiiDevTrack::Y]));
  m_device->getHeadRotationZValue()->display(static_cast<double>(payload.rotation_xyz[QTobiiDevTrack::Z]));
}

void QTobiiHeadPositionLCDDisplay::displayHeadPosition(const tobii_head_pose_t& payload) {
  display(payload);
}

}
