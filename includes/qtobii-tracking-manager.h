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
#include "qtobii-eye-position.h"
#include "qtobii-eye-position-lcd-display.h"
#include "qtobii-gaze-origin.h"
#include "qtobii-gaze-origin-lcd-display.h"
#include "qtobii-gaze-point.h"
#include "qtobii-gaze-point-lcd-display.h"
#include "qtobii-head-position.h"
#include "qtobii-head-position-lcd-display.h"
#include "qtobii-logger.h"
#include "qtobii-tracker.h"
#include "qtobii-tracking-mode.h"
#include "qtobii-user-presence.h"
#include "qtobii-user-presence-image-display.h"
#include <QObject>
#include <tobii/tobii_streams.h>

namespace qtobii {
class QTobiiTrackingManager : public QObject {

  Q_OBJECT

public:
  explicit QTobiiTrackingManager(QTobiiApi* api, QTobiiLogger* logger, QObject* parent = nullptr);
  QTobiiTrackingManager(const QTobiiTrackingManager&) = default;
  QTobiiTrackingManager(QTobiiTrackingManager&&) = default;

public slots:
  void toggleThread(const bool& value);
  void toggleSubscription(const bool& value);

private:
  void startThread();
  void stopThread();

  QTobiiApi* m_api;
  QTobiiDevTrack* m_devTrack;
  QTobiiLogger* m_logger;
  QTobiiTracker* m_tracker;
  QTobiiEyePosition* m_eyePosition;
  QTobiiEyePositionLCDDisplay* m_eyePositionDisplay;
  QTobiiGazeOrigin* m_gazeOrigin;
  QTobiiGazeOriginLCDDisplay* m_gazeOriginDisplay;
  QTobiiGazePoint* m_gazePoint;
  QTobiiGazePointLCDDisplay* m_gazePointDisplay;
  QTobiiHeadPosition* m_headPosition;
  QTobiiHeadPositionLCDDisplay* m_headPositionDisplay;
  QTobiiUserPresence* m_userPresence;
  QTobiiUserPresenceImageDisplay* m_userPresenceDisplay;

  QThread* m_thread;

};
} // namespace qtobii

#endif // QTOBIITRACKINGMANAGER_H
