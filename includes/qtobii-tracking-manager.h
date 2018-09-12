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
#include <memory>
#include <QObject>
#include <QTimer>
#include <tobii/tobii_streams.h>

namespace qtobii {

using std::shared_ptr;
using std::unique_ptr;

class QTobiiTrackingManager : public QObject {

  Q_OBJECT

public:
  explicit QTobiiTrackingManager(shared_ptr<QTobiiApi> api, shared_ptr<QTobiiLogger> logger, shared_ptr<QTobiiDevTrack> devTrack);
  QTobiiTrackingManager(const QTobiiTrackingManager&) = default;
  QTobiiTrackingManager(QTobiiTrackingManager&&) = default;

public slots:
  void toggleThread(const bool& value);
  void toggleSubscription(const bool& value);
  void toggleTimer(const bool& value);
  void processCallback();

private:
  static constexpr int CALLBACK_PROCESS_TIMER = 100;

  shared_ptr<QTobiiApi> m_api;
  shared_ptr<QTobiiDevTrack> m_devTrack;
  shared_ptr<QTobiiLogger> m_logger;

  unique_ptr<QTimer> m_timer;
  unique_ptr<QThread> m_thread;
  unique_ptr<QTobiiTracker> m_tracker;

  unique_ptr<QTobiiEyePosition> m_eyePosition;
  unique_ptr<QTobiiEyePositionLCDDisplay> m_eyePositionDisplay;
  unique_ptr<QTobiiGazeOrigin> m_gazeOrigin;
  unique_ptr<QTobiiGazeOriginLCDDisplay> m_gazeOriginDisplay;
  unique_ptr<QTobiiGazePoint> m_gazePoint;
  unique_ptr<QTobiiGazePointLCDDisplay> m_gazePointDisplay;
  unique_ptr<QTobiiHeadPosition> m_headPosition;
  unique_ptr<QTobiiHeadPositionLCDDisplay> m_headPositionDisplay;
  unique_ptr<QTobiiUserPresence> m_userPresence;
  unique_ptr<QTobiiUserPresenceImageDisplay> m_userPresenceDisplay;

  void startThread();
  void stopThread();

};
} // namespace qtobii

#endif // QTOBIITRACKINGMANAGER_H
