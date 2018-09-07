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

#ifndef QTOBIITRACKINGMODE_H
#define QTOBIITRACKINGMODE_H

namespace qtobii {
enum QTobiiTrackingMode {

  GAZE_POINT    = 0,
  GAZE_ORIGIN   = 1,
  EYE_POSITION  = 2,
  HEAD_POSITION = 4

};
} // namespace qtobii

#endif // QTOBIITRACKINGMODE_H
