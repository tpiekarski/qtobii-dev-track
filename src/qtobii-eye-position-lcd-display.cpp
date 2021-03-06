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

#include "qtobii-eye-position-lcd-display.h"

namespace qtobii {

void QTobiiEyePositionLCDDisplay::display(const tobii_eye_position_normalized_t& payload) {
  m_device->getEyePositionLeftXValue()->display(static_cast<double>(payload.left_xyz[QTobiiDevTrack::X]));
  m_device->getEyePositionLeftYValue()->display(static_cast<double>(payload.left_xyz[QTobiiDevTrack::Y]));
  m_device->getEyePositionLeftZValue()->display(static_cast<double>(payload.left_xyz[QTobiiDevTrack::Z]));
  m_device->getEyePositionRightXValue()->display(static_cast<double>(payload.right_xyz[QTobiiDevTrack::X]));
  m_device->getEyePositionRightYValue()->display(static_cast<double>(payload.right_xyz[QTobiiDevTrack::Y]));
  m_device->getEyePositionRightZValue()->display(static_cast<double>(payload.right_xyz[QTobiiDevTrack::Z]));
}

void QTobiiEyePositionLCDDisplay::displayEyePosition(const tobii_eye_position_normalized_t& payload) {
  display(payload);
}

}
