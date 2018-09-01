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
#include <QApplication>
#include <QThread>

namespace qtobii {

QTobiiTrackingManager::QTobiiTrackingManager(QObject *parent, QTobiiApi* api) : QObject(parent), api(api) {
  devTrack = dynamic_cast<QTobiiDevTrack*>(parent);
  devTrack->log("Starting Tracking Manager...");

  tracker = new QTobiiTracker(api);
  gazePoint = new QTobiiGazePoint(api, devTrack);
  thread = new QThread();

  connect(devTrack->getStartThreadButton(), &QPushButton::toggled, this, &QTobiiTrackingManager::toggleThread);
  connect(devTrack->getStartTrackingButton(), &QPushButton::toggled, this, &QTobiiTrackingManager::toggleSubscription);

  connect(tracker, &QTobiiTracker::toBeLogged, devTrack, &QTobiiDevTrack::log);
  connect(gazePoint, &QTobiiGazePoint::toBeLogged, devTrack, &QTobiiDevTrack::log);
}

void QTobiiTrackingManager::toggleThread(bool value) {
  if (value) {
    startThread();
  } else {
    stopThread();
  }
}

void QTobiiTrackingManager::toggleSubscription(bool value) {
  if (value) {
    gazePoint->subscribe();
  } else {
    gazePoint->unsubscribe();
  }
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


