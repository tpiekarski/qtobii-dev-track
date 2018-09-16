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

#include "qtobii-tracking-manager.h"
#include "qtobii-tracking-mode.h"
#include <QApplication>
#include <QThread>

namespace qtobii {

QTobiiTrackingManager::QTobiiTrackingManager(
    shared_ptr<QTobiiApi> api,
    shared_ptr<QTobiiLogger> logger,
    shared_ptr<QTobiiDevTrack> devTrack,
    const QStringList& arguments
  ) : QObject(devTrack.get()),
    m_api(api),
    m_devTrack(devTrack),
    m_logger(logger),
    m_commandLine(new QTobiiCommandLine(arguments, this)),
    m_timer(new QTimer(this)),
    m_thread(new QThread()),
    m_tracker(new QTobiiTracker(api)),
    m_eyePosition(new QTobiiEyePosition(api, this)),
    m_eyePositionDisplay(new QTobiiEyePositionLCDDisplay(m_devTrack, this)),
    m_gazeOrigin(new QTobiiGazeOrigin(api, this)),
    m_gazeOriginDisplay(new QTobiiGazeOriginLCDDisplay(m_devTrack, this)),
    m_gazePoint(new QTobiiGazePoint(api, this)),
    m_gazePointDisplay(new QTobiiGazePointLCDDisplay(m_devTrack, this)),
    m_headPosition(new QTobiiHeadPosition(api, this)),
    m_headPositionDisplay(new QTobiiHeadPositionLCDDisplay(m_devTrack, this)),
    m_userPresence(new QTobiiUserPresence(api, this)),
    m_userPresenceDisplay(new QTobiiUserPresenceImageDisplay(m_devTrack, this))
{
  logger->log("Starting Tracking Manager...");

  qRegisterMetaType<tobii_eye_position_normalized_t>("tobii_eye_position_normalized_t");
  qRegisterMetaType<tobii_gaze_origin_t>("tobii_gaze_origin_t");
  qRegisterMetaType<tobii_gaze_point_t>("tobii_gaze_point_t");
  qRegisterMetaType<tobii_head_pose_t>("tobii_head_pose_t");
  qRegisterMetaType<tobii_user_presence_status_t>("tobii_user_presence_status_t");

  connect(m_devTrack->getStartThreadButton(), &QPushButton::toggled, this, &QTobiiTrackingManager::toggleThread);
  connect(m_devTrack->getStartTrackingButton(), &QPushButton::toggled, this, &QTobiiTrackingManager::toggleSubscription);
  connect(m_devTrack->getStartTrackingButton(), &QPushButton::toggled, this, &QTobiiTrackingManager::toggleTimer);
  connect(m_thread.get(), &QThread::started, m_tracker.get(), &QTobiiTracker::start);
  connect(m_tracker.get(), &QTobiiTracker::finished, m_thread.get(), &QThread::quit);
  connect(m_tracker.get(), &QTobiiTracker::log, logger.get(), &QTobiiLogger::log);
  connect(m_tracker.get(), &QTobiiTracker::error, logger.get(), &QTobiiLogger::log);
  connect(m_eyePosition.get(), &QTobiiEyePosition::log, logger.get(), &QTobiiLogger::log);
  connect(m_gazeOrigin.get(), &QTobiiGazeOrigin::log, logger.get(), &QTobiiLogger::log);
  connect(m_gazePoint.get(), &QTobiiGazePoint::log, logger.get(), &QTobiiLogger::log);
  connect(m_headPosition.get(), &QTobiiHeadPosition::log, logger.get(), &QTobiiLogger::log);
  connect(m_userPresence.get(), &QTobiiUserPresence::log, logger.get(), &QTobiiLogger::log);
}

void QTobiiTrackingManager::toggleThread(const bool& value) {
  value ? startThread() : stopThread();
}

void QTobiiTrackingManager::toggleSubscription(const bool& value) {
  switch (m_devTrack->getTrackingMode()) {
  case QTobiiTrackingMode::GAZE_POINT:
    if (!value) {
      m_gazePoint->unsubscribe();
      m_gazePoint->getData()->disconnect();

      return;
    }

    m_gazePoint->subscribe();
    #ifdef QTOBII_MSVC_QOVERLOAD_WORKAROUND
      connect(m_gazePoint->getData(),
              static_cast<void (QTobiiDataMessenger::*)(tobii_gaze_point_t)>(&QTobiiData<tobii_gaze_point_t>::transmit),
              m_gazePointDisplay.get(), &QTobiiGazePointLCDDisplay::displayGazePoint);
    #else
      connect(gazePoint->getData(), qOverload<tobii_gaze_point_t>(&QTobiiData<tobii_gaze_point_t>::transmit),
              m_gazePointDisplay.get(), &QTobiiGazePointLCDDisplay::displayGazePoint);
    #endif
    break;

  case QTobiiTrackingMode::GAZE_ORIGIN:
    if (!value) {
      m_gazeOrigin->unsubscribe();
      m_gazeOrigin->getData()->disconnect();

      return;
    }

    m_gazeOrigin->subscribe();
    #ifdef QTOBII_MSVC_QOVERLOAD_WORKAROUND
      connect(m_gazeOrigin->getData(),
              static_cast<void (QTobiiDataMessenger::*)(tobii_gaze_origin_t)>(&QTobiiData<tobii_gaze_origin_t>::transmit),
              m_gazeOriginDisplay.get(), &QTobiiGazeOriginLCDDisplay::displayGazeOrigin);
    #else
      connect(gazeOrigin->getData(), qOverload<tobii_gaze_origin_t>(&QTobiiData<tobii_gaze_origin_t>::transmit),
              m_gazeOriginDisplay.get(), &QTobiiGazeOriginLCDDisplay::displayGazeOrigin);
    #endif

    break;

  case QTobiiTrackingMode::EYE_POSITION:
    if (!value) {
      m_eyePosition->unsubscribe();
      m_eyePosition->getData()->disconnect();

      return;
    }

    m_eyePosition->subscribe();
    #ifdef QTOBII_MSVC_QOVERLOAD_WORKAROUND
      connect(m_eyePosition->getData(),
              static_cast<void (QTobiiDataMessenger::*)(tobii_eye_position_normalized_t)>
              (&QTobiiData<tobii_eye_position_normalized_t>::transmit),
              m_eyePositionDisplay.get(), &QTobiiEyePositionLCDDisplay::displayEyePosition);
    #else
      connect(m_eyePosition->getData(), qOverload<tobii_eye_position_normalized_t>
              (&QTobiiData<tobii_eye_position_normalized_t>::transmit),
              m_eyePositionDisplay.get(), &QTobiiEyePositionLCDDisplay::displayEyePosition);
    #endif

    break;

  case QTobiiTrackingMode::USER_PRESENCE:
    if (!value) {
      m_userPresence->unsubscribe();
      m_userPresence->getData()->disconnect();

      return;
    }

    m_userPresence->subscribe();
    #ifdef QTOBII_MSVC_QOVERLOAD_WORKAROUND
      connect(m_userPresence->getData(),
              static_cast<void (QTobiiDataMessenger::*)(tobii_user_presence_status_t)>
              (&QTobiiData<tobii_user_presence_status_t>::transmit),
              m_userPresenceDisplay.get(), &QTobiiUserPresenceImageDisplay::displayUserPresence);
    #else
      connect(m_userPresence->getData(), qOverload<tobii_user_presence_status_t>
              (&QTobiiData<tobii_user_presence_status_t>::transmit),
              m_userPresenceDisplay.get(), &QTobiiUserPresenceImageDisplay::displayUserPresence);
    #endif

    connect(m_userPresence->getData(), &QObject::destroyed,
            m_userPresenceDisplay.get(), &QTobiiUserPresenceImageDisplay::resetUserPresence);

    break;

  case QTobiiTrackingMode::HEAD_POSITION:
    if (!value) {
      m_headPosition->unsubscribe();
      m_headPosition->getData()->disconnect();

      return;
    }

    m_headPosition->subscribe();
    #ifdef QTOBII_MSVC_QOVERLOAD_WORKAROUND
      connect(m_headPosition->getData(),
              static_cast<void (QTobiiDataMessenger::*)(tobii_head_pose_t)>(&QTobiiData<tobii_head_pose_t>::transmit),
              m_headPositionDisplay.get(), &QTobiiHeadPositionLCDDisplay::displayHeadPosition);
    #else
      connect(m_headPosition->getData(), qOverload<tobii_head_pose_t>(&QTobiiData<tobii_head_position_normalized_t>::transmit),
              m_headPositionDisplay.get(), &QTobiiHeadPositionLCDDisplay::displayHeadPosition);
    #endif

    break;

  }
}

void QTobiiTrackingManager::toggleTimer(const bool& value) {
  if (!value) {
    if (m_timer->isActive()) {
      m_timer->stop();
    }

    m_timer->disconnect();

    return;
  }

  connect(m_timer.get(), &QTimer::timeout, this, &QTobiiTrackingManager::processCallback);
  m_timer->start(m_commandLine->getProcessCallbackIntervall());
}

void QTobiiTrackingManager::processCallback() {
  m_api->call(tobii_device_process_callbacks(m_api->getDevice()));
}

void QTobiiTrackingManager::startThread() {
  m_tracker->moveToThread(m_thread.get());
  m_thread->start();
}

void QTobiiTrackingManager::stopThread() {
  m_tracker->stop();
}

} // namespace qtobii


