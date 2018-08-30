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

void QTobiiGazePoint::callback(const tobii_gaze_point_t *gazePoint, void *data) {
  QString output = QString("%1/%2").arg(
    QString::number(gazePoint->position_xy[0]),
    QString::number(gazePoint->position_xy[1])
  );

  qDebug() << output;

  // todo: send custom event containing data
}

void QTobiiGazePoint::subscribe() {
  emit toBeLogged("Subscribing to gaze point...");
  api->setup(tobii_gaze_point_subscribe(api->getDevice(), callback, NULL));
}

void QTobiiGazePoint::unsubscribe() {
  emit toBeLogged("Unsubscribing from gaze point...");
  api->setup(tobii_gaze_point_unsubscribe(api->getDevice()));
}

QString QTobiiGazePoint::getDescription() {
  return "Class for tracking gaze point X/Y-coordinates.";
}

} // namespace qtobii
