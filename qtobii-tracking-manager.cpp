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
#include <QDebug>

namespace qtobii {

QTobiiTrackingManager::QTobiiTrackingManager(QObject *parent, QTobiiApi* api) : QObject(parent), api(api) {
  devTrack = dynamic_cast<QTobiiDevTrack*>(parent);
  devTrack->log("Starting Tracking Manager...");

  gazePointTracker = new QTobiiGazePoint(api);

  thread = new QThread();

  gazePointTracker->moveToThread(thread);
  connect(thread, &QThread::started, gazePointTracker, &QTobiiGazePoint::track);
  connect(gazePointTracker, &QTobiiGazePoint::finished, thread, &QThread::quit);
  connect(thread, &QThread::finished, gazePointTracker, &QObject::deleteLater);
  connect(thread, &QThread::finished, thread, &QThread::deleteLater);

  connect(devTrack->getThreadTrackingButton(), &QPushButton::toggled, this, &QTobiiTrackingManager::toggleThread);
  connect(devTrack->getStartTrackingButton(), &QPushButton::toggled, this, &QTobiiTrackingManager::toggleSubscription);
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
    gazePointTracker->subscribe();
  } else {
    gazePointTracker->unsubscribe();
  }
}

void QTobiiTrackingManager::startThread() {
  qDebug() << "Finished/Running: " << thread->isFinished() << "/" << thread->isRunning();
  gazePointTracker->start();
  thread->start();
}

void QTobiiTrackingManager::stopThread() {
  gazePointTracker->stop();
}

} // namespace qtobii


