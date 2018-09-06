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

namespace qtobii {

QTobiiDevTrack::QTobiiDevTrack(QWidget *parent) : QMainWindow(parent), ui(new Ui::QTobiiDevTrackWindow) {
  ui->setupUi(this);

  ui->dataLog->setReadOnly(true);
  ui->messageLog->setReadOnly(true);

  connect(ui->startThreadButton, &QPushButton::toggled, this, &QTobiiDevTrack::onStartThreadButtonToggled);
  connect(ui->startTrackingButton, &QPushButton::toggled, this, &QTobiiDevTrack::onStartTrackingButtonToggled);
}

QTobiiDevTrack::~QTobiiDevTrack() {
  if (ui != nullptr) {
    delete ui;
    ui = nullptr;
  }
}

QTobiiTrackingMode QTobiiDevTrack::getTrackingMode() {
  return static_cast<QTobiiTrackingMode>(ui->trackingBox->currentIndex());
}

// todo: check why inline definitions of all these methods are not possible
QPushButton* QTobiiDevTrack::getStartThreadButton() { return ui->startThreadButton; }
QPushButton* QTobiiDevTrack::getStartTrackingButton() { return ui->startTrackingButton; }
QPlainTextEdit* QTobiiDevTrack::getDataLog() { return ui->dataLog; }
QPlainTextEdit* QTobiiDevTrack::getMessageLog() { return ui->messageLog; }
QLCDNumber* QTobiiDevTrack::getGazePointXValue() { return ui->gazePointXValue; }
QLCDNumber* QTobiiDevTrack::getGazePointYValue() { return ui->gazePointYValue; }
QLCDNumber* QTobiiDevTrack::getGazeOriginLeftXValue() { return ui->gazeOriginLeftEyeXValue; }
QLCDNumber* QTobiiDevTrack::getGazeOriginLeftYValue() { return ui->gazeOriginLeftEyeYValue; }
QLCDNumber* QTobiiDevTrack::getGazeOriginLeftZValue() { return ui->gazeOriginLeftEyeZValue; }
QLCDNumber* QTobiiDevTrack::getGazeOriginRightXValue() { return ui->gazeOriginRightEyeXValue; }
QLCDNumber* QTobiiDevTrack::getGazeOriginRightYValue() { return ui->gazeOriginRightEyeYValue; }
QLCDNumber* QTobiiDevTrack::getGazeOriginRightZValue() { return ui->gazeOriginRightEyeZValue; }

void QTobiiDevTrack::onStartThreadButtonToggled(bool value) {
  ui->startTrackingButton->setEnabled(value);

  if (value) {
    ui->startThreadButton->setText("Stop Tracking &Thread");
  } else {
    ui->startThreadButton->setText("Start Tracking &Thread");
  }

}

void QTobiiDevTrack::onStartTrackingButtonToggled(bool value) {
  ui->startThreadButton->setEnabled(!value);

  if (value) {
    ui->startTrackingButton->setText("&Stop Tracking");
  } else {
    ui->startTrackingButton->setText("&Start Tracking");
  }
}

} // namesapce qtobii


