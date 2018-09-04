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

#ifndef QTOBIITRACKINGMANAGER_H
#define QTOBIITRACKINGMANAGER_H

#include "qtobii-api.h"
#include "qtobii-dev-track.h"
#include "qtobii-gaze-point.h"
#include "qtobii-logger.h"
#include "qtobii-tracker.h"
#include <QObject>
#include <tobii/tobii_streams.h>

namespace qtobii {
class QTobiiTrackingManager : public QObject {

  Q_OBJECT

public:
  explicit QTobiiTrackingManager(QObject *parent, QTobiiApi* api, QTobiiLogger* logger);

public slots:
  void toggleThread(bool value);
  void toggleSubscription(bool value);
  void displayGazePointData(tobii_gaze_point_t data);

private:
  void startThread();
  void stopThread();

  QTobiiApi* api;
  QTobiiDevTrack* devTrack;
  QTobiiLogger* logger;
  QTobiiTracker* tracker;
  QTobiiGazePoint* gazePoint;
  QThread* thread;

};
} // namespace qtobii

#endif // QTOBIITRACKINGMANAGER_H
