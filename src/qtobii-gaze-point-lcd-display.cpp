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

#include "qtobii-gaze-point-lcd-display.h"

namespace qtobii {

void QTobiiGazePointLCDDisplay::display(const tobii_gaze_point_t& payload) {
  m_device->getGazePointXValue()->display(static_cast<double>(payload.position_xy[QTobiiDevTrack::X]));
  m_device->getGazePointYValue()->display(static_cast<double>(payload.position_xy[QTobiiDevTrack::Y]));
}

void QTobiiGazePointLCDDisplay::displayGazePoint(const tobii_gaze_point_t& payload) {
  display(payload);
}

} // namespace qtobii
