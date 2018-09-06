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

#include "interfaces/qtobii-display.h"
#include "qtobii-api.h"
#include "qtobii-dev-track.h"
#include "qtobii-gaze-origin.h"
#include "qtobii-gaze-point.h"
#include "qtobii-gaze-point-lcd-display.h"
#include "qtobii-logger.h"
#include "qtobii-tracker.h"
#include "qtobii-tracking-mode.h"
#include <QObject>
#include <tobii/tobii_streams.h>

namespace qtobii {
class QTobiiTrackingManager : public QObject {

  Q_OBJECT

public:
  explicit QTobiiTrackingManager(QObject* parent, QTobiiApi* api, QTobiiLogger* logger);
  QTobiiTrackingManager(const QTobiiTrackingManager&) = default;
  QTobiiTrackingManager(QTobiiTrackingManager&&) = default;

public slots:
  void toggleThread(bool value);
  void toggleSubscription(bool value);
  void displayGazeOriginData(tobii_gaze_origin_t data);

private:
  void startThread();
  void stopThread();

  QTobiiApi* m_api;
  QTobiiDevTrack* m_devTrack;
  QTobiiLogger* m_logger;
  QTobiiTracker* m_tracker;
  QTobiiGazeOrigin* m_gazeOrigin;
  QTobiiGazePoint* m_gazePoint;
  QTobiiGazePointLCDDisplay* m_gazePointDisplay;

  QThread* m_thread;

};
} // namespace qtobii

#endif // QTOBIITRACKINGMANAGER_H
