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
    shared_ptr<QTobiiApi> api, shared_ptr<QTobiiLogger> logger, shared_ptr<QTobiiDevTrack> devTrack
  ) : QObject(devTrack.get()),
    m_api(api),
    m_devTrack(devTrack),
    m_logger(logger),
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
    m_userPresenceDisplay(new QTobiiUserPresenceImageDisplay(m_devTrack, this)),
    m_thread(new QThread())
{
  logger->log("Starting Tracking Manager...");

  qRegisterMetaType<tobii_eye_position_normalized_t>("tobii_eye_position_normalized_t");
  qRegisterMetaType<tobii_gaze_origin_t>("tobii_gaze_origin_t");
  qRegisterMetaType<tobii_gaze_point_t>("tobii_gaze_point_t");
  qRegisterMetaType<tobii_head_pose_t>("tobii_head_pose_t");
  qRegisterMetaType<tobii_user_presence_status_t>("tobii_user_presence_status_t");

  connect(m_devTrack->getStartThreadButton(), &QPushButton::toggled, this, &QTobiiTrackingManager::toggleThread);
  connect(m_devTrack->getStartTrackingButton(), &QPushButton::toggled, this, &QTobiiTrackingManager::toggleSubscription);
  connect(m_tracker, &QTobiiTracker::log, logger.get(), &QTobiiLogger::log);
  connect(m_tracker, &QTobiiTracker::error, logger.get(), &QTobiiLogger::log);
  connect(m_eyePosition, &QTobiiEyePosition::log, logger.get(), &QTobiiLogger::log);
  connect(m_gazeOrigin, &QTobiiGazeOrigin::log, logger.get(), &QTobiiLogger::log);
  connect(m_gazePoint, &QTobiiGazePoint::log, logger.get(), &QTobiiLogger::log);
  connect(m_headPosition, &QTobiiHeadPosition::log, logger.get(), &QTobiiLogger::log);
  connect(m_userPresence, &QTobiiUserPresence::log, logger.get(), &QTobiiLogger::log);
}

void QTobiiTrackingManager::toggleThread(const bool& value) {
  value ? startThread() : stopThread();
}

void QTobiiTrackingManager::toggleSubscription(const bool& value) {
  switch (m_devTrack->getTrackingMode()) {
  case QTobiiTrackingMode::GAZE_POINT:
    if (!value) {
      m_gazePoint->unsubscribe();
      return;
    }

    m_gazePoint->subscribe();
    #ifdef QTOBII_MSVC_QOVERLOAD_WORKAROUND
      connect(m_gazePoint->getData(),
              static_cast<void (QTobiiDataMessenger::*)(tobii_gaze_point_t)>(&QTobiiData<tobii_gaze_point_t>::transmit),
              m_gazePointDisplay, &QTobiiGazePointLCDDisplay::displayGazePoint);
    #else
      connect(gazePoint->getData(), qOverload<tobii_gaze_point_t>(&QTobiiData<tobii_gaze_point_t>::transmit),
              m_gazePointDisplay, &QTobiiGazePointLCDDisplay::displayGazePoint);
    #endif
    break;

  case QTobiiTrackingMode::GAZE_ORIGIN:
    if (!value) {
      m_gazeOrigin->unsubscribe();

      return;
    }

    m_gazeOrigin->subscribe();
    #ifdef QTOBII_MSVC_QOVERLOAD_WORKAROUND
      connect(m_gazeOrigin->getData(),
              static_cast<void (QTobiiDataMessenger::*)(tobii_gaze_origin_t)>(&QTobiiData<tobii_gaze_origin_t>::transmit),
              m_gazeOriginDisplay, &QTobiiGazeOriginLCDDisplay::displayGazeOrigin);
    #else
      connect(gazeOrigin->getData(), qOverload<tobii_gaze_origin_t>(&QTobiiData<tobii_gaze_origin_t>::transmit),
              m_gazeOriginDisplay, &QTobiiGazeOriginLCDDisplay::displayGazeOrigin);
    #endif

    break;

  case QTobiiTrackingMode::EYE_POSITION:
    if (!value) {
      m_eyePosition->unsubscribe();

      return;
    }

    m_eyePosition->subscribe();
    #ifdef QTOBII_MSVC_QOVERLOAD_WORKAROUND
      connect(m_eyePosition->getData(),
              static_cast<void (QTobiiDataMessenger::*)(tobii_eye_position_normalized_t)>
              (&QTobiiData<tobii_eye_position_normalized_t>::transmit),
              m_eyePositionDisplay, &QTobiiEyePositionLCDDisplay::displayEyePosition);
    #else
      connect(m_eyePosition->getData(), qOverload<tobii_eye_position_normalized_t>
              (&QTobiiData<tobii_eye_position_normalized_t>::transmit),
              m_eyePositionDisplay, &QTobiiEyePositionLCDDisplay::displayEyePosition);
    #endif

    break;

  case QTobiiTrackingMode::USER_PRESENCE:
    if (!value) {
      m_userPresence->unsubscribe();

      return;
    }

    m_userPresence->subscribe();
    #ifdef QTOBII_MSVC_QOVERLOAD_WORKAROUND
      connect(m_userPresence->getData(),
              static_cast<void (QTobiiDataMessenger::*)(tobii_user_presence_status_t)>
              (&QTobiiData<tobii_user_presence_status_t>::transmit),
              m_userPresenceDisplay, &QTobiiUserPresenceImageDisplay::displayUserPresence);
    #else
      connect(m_userPresence->getData(), qOverload<tobii_user_presence_status_t>
              (&QTobiiData<tobii_user_presence_status_t>::transmit),
              m_userPresenceDisplay, &QTobiiUserPresenceImageDisplay::displayUserPresence);
    #endif

    connect(m_userPresence->getData(), &QObject::destroyed,
            m_userPresenceDisplay, &QTobiiUserPresenceImageDisplay::resetUserPresence);

    break;

  case QTobiiTrackingMode::HEAD_POSITION:
    if (!value) {
      m_headPosition->unsubscribe();

      return;
    }

    m_headPosition->subscribe();
    #ifdef QTOBII_MSVC_QOVERLOAD_WORKAROUND
      connect(m_headPosition->getData(),
              static_cast<void (QTobiiDataMessenger::*)(tobii_head_pose_t)>(&QTobiiData<tobii_head_pose_t>::transmit),
              m_headPositionDisplay, &QTobiiHeadPositionLCDDisplay::displayHeadPosition);
    #else
      connect(m_headPosition->getData(), qOverload<tobii_head_pose_t>(&QTobiiData<tobii_head_position_normalized_t>::transmit),
              m_headPositionDisplay, &QTobiiHeadPositionLCDDisplay::displayHeadPosition);
    #endif

    break;

  }
}

void QTobiiTrackingManager::startThread() {
  m_tracker->moveToThread(m_thread);
  connect(m_thread, &QThread::started, m_tracker, &QTobiiTracker::start);
  connect(m_tracker, &QTobiiTracker::finished, m_thread, &QThread::quit);
  connect(m_thread, &QThread::finished, m_tracker, &QObject::deleteLater);
  connect(m_thread, &QThread::finished, m_thread, &QThread::deleteLater);
  m_thread->start();
}

void QTobiiTrackingManager::stopThread() {
  m_tracker->stop();
}

} // namespace qtobii


