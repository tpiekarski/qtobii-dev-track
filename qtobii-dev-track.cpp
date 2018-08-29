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

#include "qtobii-dev-track.h"
#include "ui_qtobii-dev-track-window.h"
#include <QDebug>

namespace qtobii {

QTobiiDevTrack::QTobiiDevTrack(QWidget *parent) : QMainWindow(parent), ui(new Ui::QTobiiDevTrackWindow) {
  ui->setupUi(this);

  connect(ui->threadTrackingButton, &QPushButton::toggled, this, &QTobiiDevTrack::onThreadTrackingButtonToggled);
  connect(ui->startTrackingButton, &QPushButton::toggled, this, &QTobiiDevTrack::onStartTrackingButtonToggled);
}

QTobiiDevTrack::~QTobiiDevTrack() {
  if (ui != nullptr) {
    delete ui;
    ui = nullptr;
  }
}

void QTobiiDevTrack::log(QString message) {
  if (!message.isEmpty()) {
    ui->logBrowser->appendPlainText(message);
  }
}

QPushButton* QTobiiDevTrack::getThreadTrackingButton() { return ui->threadTrackingButton; }
QPushButton* QTobiiDevTrack::getStartTrackingButton() { return ui->startTrackingButton; }

void QTobiiDevTrack::onThreadTrackingButtonToggled(bool value) {
  ui->startTrackingButton->setEnabled(value);

  if (value) {
    log("Starting thread for tracking...");
    ui->threadTrackingButton->setText("Stop Tracking &Thread");
  } else {
    log("Stopping thread for tracking...");
    ui->threadTrackingButton->setText("Start Tracking &Thread");
  }

}

void QTobiiDevTrack::onStartTrackingButtonToggled(bool value) {
  ui->threadTrackingButton->setEnabled(!value);

  if (value) {
    // todo: subscribe to tracking data
    log("Starting tracking...");
    ui->startTrackingButton->setText("&Stop Tracking");
  } else {
    // todo: unsubscribe from tracking data
    log("Stopping tracking...");
    ui->startTrackingButton->setText("&Start Tracking");
  }
}

} // namesapce qtobii


