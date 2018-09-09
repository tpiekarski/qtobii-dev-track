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

QTobiiDevTrack::QTobiiDevTrack(QWidget* parent) : QMainWindow(parent), m_ui(new Ui::QTobiiDevTrackWindow) {
  m_ui->setupUi(this);
  m_ui->dataLog->setReadOnly(true);
  m_ui->messageLog->setReadOnly(true);

  connect(m_ui->startThreadButton, &QPushButton::toggled, this, &QTobiiDevTrack::onStartThreadButtonToggled);
  connect(m_ui->startTrackingButton, &QPushButton::toggled, this, &QTobiiDevTrack::onStartTrackingButtonToggled);
}

QTobiiDevTrack::~QTobiiDevTrack() {
  if (m_ui != nullptr) {
    delete m_ui;
    m_ui = nullptr;
  }
}

QTobiiTrackingMode QTobiiDevTrack::getTrackingMode() {
  return static_cast<QTobiiTrackingMode>(m_ui->trackingBox->currentIndex());
}

void QTobiiDevTrack::onStartThreadButtonToggled(const bool& value) {
  m_ui->startTrackingButton->setEnabled(value);
  m_ui->startThreadButton->setText((value) ? "Stop Tracking &Thread" : "Start Tracking &Thread");
}

void QTobiiDevTrack::onStartTrackingButtonToggled(const bool& value) {
  m_ui->startThreadButton->setEnabled(!value);
  m_ui->startTrackingButton->setText((value) ? "&Stop Tracking" : "&Start Tracking");
}

} // namesapce qtobii


