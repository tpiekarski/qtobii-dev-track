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

void QTobiiDevTrack::onStartThreadButtonToggled(bool value) {
  ui->startTrackingButton->setEnabled(value);
  ui->startThreadButton->setText((value) ? "Stop Tracking &Thread" : "Start Tracking &Thread");
}

void QTobiiDevTrack::onStartTrackingButtonToggled(bool value) {
  ui->startThreadButton->setEnabled(!value);
  ui->startTrackingButton->setText((value) ? "&Stop Tracking" : "&Start Tracking");
}

} // namesapce qtobii


