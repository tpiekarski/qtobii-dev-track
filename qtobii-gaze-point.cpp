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
#include <QDebug>

namespace qtobii {

void QTobiiGazePoint::track() {
  tobii_device_t* const device = api->getDevice();
  QTobiiResult* result = nullptr;

  do {
    qDebug() << "track-track-track....";

    result = api->call(tobii_wait_for_callbacks(NULL, 1, &device));

    if (result->getError() == TOBII_ERROR_TIMED_OUT) {
      continue;
    }

    api->call(tobii_device_process_callbacks(device));

    delete result;
    result = nullptr;
  } while (tracking);

  qDebug() << "emiting finished signal";
  emit finished();
}

void QTobiiGazePoint::callback(const tobii_gaze_point_t *gazePoint, void *data) {
  qDebug() << gazePoint->position_xy[0] << "/" << gazePoint->position_xy[1];

  //QPair<float, float> point(gazePoint->position_xy[0], gazePoint->position_xy[1]);
  //emit dataReceived(point);
}

void QTobiiGazePoint::subscribe() {
  qDebug() << "Subscribing";
  api->setup(tobii_gaze_point_subscribe(api->getDevice(), callback, NULL));
}

void QTobiiGazePoint::unsubscribe() {
  qDebug() << "Unsubscribing";
  api->setup(tobii_gaze_point_unsubscribe(api->getDevice()));
}

QString QTobiiGazePoint::getDescription() {
  return "Class for tracking gaze point X/Y-coordinates.";
}

} // namespace qtobii
