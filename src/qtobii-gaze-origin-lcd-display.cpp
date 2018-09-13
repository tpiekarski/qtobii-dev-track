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

#include "qtobii-gaze-origin-lcd-display.h"

namespace qtobii {

void QTobiiGazeOriginLCDDisplay::display(const tobii_gaze_origin_t& payload) {
  m_device->getGazeOriginLeftXValue()->display(static_cast<double>(payload.left_xyz[QTobiiDevTrack::X]));
  m_device->getGazeOriginLeftYValue()->display(static_cast<double>(payload.left_xyz[QTobiiDevTrack::Y]));
  m_device->getGazeOriginLeftZValue()->display(static_cast<double>(payload.left_xyz[QTobiiDevTrack::Z]));
  m_device->getGazeOriginRightXValue()->display(static_cast<double>(payload.right_xyz[QTobiiDevTrack::X]));
  m_device->getGazeOriginRightYValue()->display(static_cast<double>(payload.right_xyz[QTobiiDevTrack::Y]));
  m_device->getGazeOriginRightZValue()->display(static_cast<double>(payload.right_xyz[QTobiiDevTrack::Z]));
}

void QTobiiGazeOriginLCDDisplay::displayGazeOrigin(const tobii_gaze_origin_t& payload) {
  display(payload);
}


}

