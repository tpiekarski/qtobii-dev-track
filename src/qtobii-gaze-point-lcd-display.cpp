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
#include <cmath>

namespace qtobii {

void QTobiiGazePointLCDDisplay::display(const tobii_gaze_point_t& payload) {
  m_device->denormalizeGazePoint() ? displayDenormalized(payload) : displayNormalized(payload);
}

void QTobiiGazePointLCDDisplay::displayGazePoint(const tobii_gaze_point_t& payload) {
  display(payload);
}

void QTobiiGazePointLCDDisplay::displayNormalized(const tobii_gaze_point_t& payload) {
  m_device->getGazePointXValue()->display(static_cast<double>(payload.position_xy[QTobiiDevTrack::X]));
  m_device->getGazePointYValue()->display(static_cast<double>(payload.position_xy[QTobiiDevTrack::Y]));
}

void QTobiiGazePointLCDDisplay::displayDenormalized(const tobii_gaze_point_t& payload) {
  const float width = static_cast<float>(m_device->getScreenSize().width());
  const float height = static_cast<float>(m_device->getScreenSize().height());

  float x = width * payload.position_xy[QTobiiDevTrack::X];
  float y = height * payload.position_xy[QTobiiDevTrack::Y];

  x = (x > 0 && x < width)  ? roundf(x) : ((x < 0) ? 0 : width);
  y = (y > 0 && y < height) ? roundf(y) : ((y < 0) ? 0 : height);

  m_device->getGazePointXValue()->display(static_cast<int>(x));
  m_device->getGazePointYValue()->display(static_cast<int>(y));
}

} // namespace qtobii
