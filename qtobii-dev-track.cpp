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

  connect(ui->startThreadButton, &QPushButton::toggled, this, &QTobiiDevTrack::onStartThreadButtonToggled);
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

QPushButton* QTobiiDevTrack::getStartThreadButton() { return ui->startThreadButton; }
QPushButton* QTobiiDevTrack::getStartTrackingButton() { return ui->startTrackingButton; }

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


