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

QTobiiTrackingManager::QTobiiTrackingManager(QObject* parent, QTobiiApi* api, QTobiiLogger* logger)
  : QObject(parent),
    m_api(api),
    m_devTrack(dynamic_cast<QTobiiDevTrack*>(parent)),
    m_logger(logger),
    m_tracker(new QTobiiTracker(nullptr, api)),
    m_gazeOrigin(new QTobiiGazeOrigin(this, api)),
    m_gazePoint(new QTobiiGazePoint(this, api)),
    m_gazePointDisplay(new QTobiiGazePointLCDDisplay(m_devTrack, this)),
    m_thread(new QThread())
{
  logger->log("Starting Tracking Manager...");

  qRegisterMetaType<tobii_gaze_origin_t>("tobii_gaze_origin_t");
  qRegisterMetaType<tobii_gaze_point_t>("tobii_gaze_point_t");

  connect(m_devTrack->getStartThreadButton(), &QPushButton::toggled, this, &QTobiiTrackingManager::toggleThread);
  connect(m_devTrack->getStartTrackingButton(), &QPushButton::toggled, this, &QTobiiTrackingManager::toggleSubscription);
  connect(m_tracker, &QTobiiTracker::log, logger, &QTobiiLogger::log);
  connect(m_tracker, &QTobiiTracker::error, logger, &QTobiiLogger::log);
  connect(m_gazeOrigin, &QTobiiGazeOrigin::log, logger, &QTobiiLogger::log);
  connect(m_gazePoint, &QTobiiGazePoint::log, logger, &QTobiiLogger::log);
}

void QTobiiTrackingManager::toggleThread(bool value) {
  value ? startThread() : stopThread();
}

void QTobiiTrackingManager::toggleSubscription(bool value) {
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
              this, &QTobiiTrackingManager::displayGazePointData);
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
              this, &QTobiiTrackingManager::displayGazeOriginData);
    #else
      connect(gazeOrigin->getData(), qOverload<tobii_gaze_origin_t>(&QTobiiData<tobii_gaze_origin_t>::transmit),
              this, &QTobiiTrackingManager::displayGazeOriginData);
    #endif

    break;

  default:
    m_logger->log("Selected tracking is not yet implemented.");

    break;
  }
}

void QTobiiTrackingManager::displayGazeOriginData(tobii_gaze_origin_t data) {
  m_devTrack->getGazeOriginLeftXValue()->display(static_cast<double>(data.left_xyz[0]));
  m_devTrack->getGazeOriginLeftYValue()->display(static_cast<double>(data.left_xyz[1]));
  m_devTrack->getGazeOriginLeftZValue()->display(static_cast<double>(data.left_xyz[2]));
  m_devTrack->getGazeOriginRightXValue()->display(static_cast<double>(data.right_xyz[0]));
  m_devTrack->getGazeOriginRightYValue()->display(static_cast<double>(data.right_xyz[1]));
  m_devTrack->getGazeOriginRightZValue()->display(static_cast<double>(data.right_xyz[2]));
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


