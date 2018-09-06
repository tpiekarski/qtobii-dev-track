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

QTobiiTrackingManager::QTobiiTrackingManager(QObject *parent, QTobiiApi* api, QTobiiLogger* logger)
  : QObject(parent),
    api(api),
    devTrack(dynamic_cast<QTobiiDevTrack*>(parent)),
    logger(logger),
    tracker(new QTobiiTracker(nullptr, api)),
    gazeOrigin(new QTobiiGazeOrigin(this, api)),
    gazePoint(new QTobiiGazePoint(this, api)),
    thread(new QThread())
{
  logger->log("Starting Tracking Manager...");

  qRegisterMetaType<tobii_gaze_origin_t>("tobii_gaze_origin_t");
  qRegisterMetaType<tobii_gaze_point_t>("tobii_gaze_point_t");

  connect(devTrack->getStartThreadButton(), &QPushButton::toggled, this, &QTobiiTrackingManager::toggleThread);
  connect(devTrack->getStartTrackingButton(), &QPushButton::toggled, this, &QTobiiTrackingManager::toggleSubscription);
  connect(tracker, &QTobiiTracker::log, logger, &QTobiiLogger::log);
  connect(tracker, &QTobiiTracker::error, logger, &QTobiiLogger::log);
  connect(gazeOrigin, &QTobiiGazeOrigin::log, logger, &QTobiiLogger::log);
  connect(gazePoint, &QTobiiGazePoint::log, logger, &QTobiiLogger::log);
}

void QTobiiTrackingManager::toggleThread(bool value) {
  value ? startThread() : stopThread();
}

void QTobiiTrackingManager::toggleSubscription(bool value) {
  switch (devTrack->getTrackingMode()) {
  case QTobiiTrackingMode::GAZE_POINT:
    if (!value) {
      gazePoint->unsubscribe();
      return;
    }

    gazePoint->subscribe();
    #ifdef QTOBII_MSVC_QOVERLOAD_WORKAROUND
      connect(gazePoint->getData(),
              static_cast<void (QTobiiDataMessenger::*)(tobii_gaze_point_t)>(&QTobiiData<tobii_gaze_point_t>::transmit),
              this, &QTobiiTrackingManager::displayGazePointData);
    #else
      connect(gazePoint->getData(), qOverload<tobii_gaze_point_t>(&QTobiiData<tobii_gaze_point_t>::transmit),
              this, &QTobiiTrackingManager::displayGazePointData);
    #endif
    break;

  case QTobiiTrackingMode::GAZE_ORIGIN:
    if (!value) {
      gazeOrigin->unsubscribe();

      return;
    }

    gazeOrigin->subscribe();
    #ifdef QTOBII_MSVC_QOVERLOAD_WORKAROUND
      connect(gazeOrigin->getData(),
              static_cast<void (QTobiiDataMessenger::*)(tobii_gaze_origin_t)>(&QTobiiData<tobii_gaze_origin_t>::transmit),
              this, &QTobiiTrackingManager::displayGazeOriginData);
    #else
      connect(gazeOrigin->getData(), qOverload<tobii_gaze_origin_t>(&QTobiiData<tobii_gaze_origin_t>::transmit),
              this, &QTobiiTrackingManager::displayGazeOriginData);
    #endif

    break;

  default:
    logger->log("Selected tracking is not yet implemented.");

    break;
  }
}

void QTobiiTrackingManager::displayGazeOriginData(tobii_gaze_origin_t data) {
  devTrack->getGazeOriginLeftXValue()->display(static_cast<double>(data.left_xyz[0]));
  devTrack->getGazeOriginLeftYValue()->display(static_cast<double>(data.left_xyz[1]));
  devTrack->getGazeOriginLeftZValue()->display(static_cast<double>(data.left_xyz[2]));
  devTrack->getGazeOriginRightXValue()->display(static_cast<double>(data.right_xyz[0]));
  devTrack->getGazeOriginRightYValue()->display(static_cast<double>(data.right_xyz[1]));
  devTrack->getGazeOriginRightZValue()->display(static_cast<double>(data.right_xyz[2]));
}

void QTobiiTrackingManager::displayGazePointData(tobii_gaze_point_t data) {
  devTrack->getGazePointXValue()->display(static_cast<double>(data.position_xy[0]));
  devTrack->getGazePointYValue()->display(static_cast<double>(data.position_xy[1]));
}

void QTobiiTrackingManager::startThread() {
  tracker->moveToThread(thread);
  connect(thread, &QThread::started, tracker, &QTobiiTracker::start);
  connect(tracker, &QTobiiTracker::finished, thread, &QThread::quit);
  connect(thread, &QThread::finished, tracker, &QObject::deleteLater);
  connect(thread, &QThread::finished, thread, &QThread::deleteLater);
  thread->start();
}

void QTobiiTrackingManager::stopThread() {
  tracker->stop();
}

} // namespace qtobii


