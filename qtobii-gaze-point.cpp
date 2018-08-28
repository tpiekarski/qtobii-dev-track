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

#include "qtobii-gaze-point.h"

namespace qtobii {

// todo: implement interface QTobiiPlugin

QTobiiGazePoint::QTobiiGazePoint() {
  // todo: implement contstructor
}

/*
QTobiiResult QTobiiGazePoint::subscribe(tobii_device_t* device) {
  // todo: implement subscribe
}

QTobiiResult QTobiiGazePoint::unsubscribe(tobii_device_t* device) {
  // todo: implement unsubscribe
}
*/

QString QTobiiGazePoint::getDescription() {
  return "Class for tracking gaze point X/Y-coordinates.";
}

} // namespace qtobii