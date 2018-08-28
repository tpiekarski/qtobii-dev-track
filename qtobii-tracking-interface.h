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

#ifndef QTOBII_TRACKING_INTERFACE_H
#define QTOBII_TRACKING_INTERFACE_H

#include "qtobii-api.h"
#include "qtobii-result.h"
#include <QString>
#include <tobii.h>

namespace qtobii {
class QTobiiTrackingInterface {

public:
  virtual ~QTobiiTrackingInterface() {
    // Only defined to make sure all destructors will be called along inheritance.
  }

  //virtual QTobiiResult subscribe(tobii_device_t* device) = 0;
  //virtual QTobiiResult unsubscribe(tobii_device_t* device) = 0;
  virtual QString getDescription() = 0;

};
} // namespace qtobii
#endif
