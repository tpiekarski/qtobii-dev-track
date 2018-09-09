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

#include "qtobii-result.h"
#include "qtobii-tracker.h"
#include <tobii/tobii.h>
#include <tobii/tobii_streams.h>
#include <QDebug>

namespace qtobii {

void QTobiiTracker::start() {
  emit log("Starting tracking thread.");
  tobii_device_t* const device = m_api->getDevice();
  m_tracking = true;

  do {
    shared_ptr<QTobiiResult> result(m_api->call(tobii_wait_for_callbacks(nullptr, DEFAULT_DEVICE, &device)));

    if (result->getError() == TOBII_ERROR_TIMED_OUT) {
      continue;
    }

    m_api->call(tobii_device_process_callbacks(device));
    result.reset();
  } while (m_tracking);

  emit log("Tracking thread has finished.");
  emit finished();
}

void QTobiiTracker::stop() {
  emit log("Stopping tracking thread.");
  m_tracking = false;
}

}
