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

#ifndef QTOBII_DEV_TRACK_H
#define QTOBII_DEV_TRACK_H

#include "qtobii-tracking-mode.h"
#include <QLCDNumber>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QPushButton>

#include "ui_qtobii-dev-track-window.h"

namespace qtobii {
class QTobiiDevTrack : public QMainWindow {

  Q_OBJECT

public:
  explicit QTobiiDevTrack(QWidget *parent = nullptr);
  ~QTobiiDevTrack();

  QTobiiTrackingMode getTrackingMode();

  QPushButton* getStartThreadButton() { return ui->startThreadButton; }
  QPushButton* getStartTrackingButton() { return ui->startTrackingButton; }
  QPlainTextEdit* getDataLog() { return ui->dataLog; }
  QPlainTextEdit* getMessageLog() { return ui->messageLog; }

  QLCDNumber* getGazePointXValue() { return ui->gazePointXValue; }
  QLCDNumber* getGazePointYValue() { return ui->gazePointYValue; }

  QLCDNumber* getGazeOriginLeftXValue() { return ui->gazeOriginLeftEyeXValue; }
  QLCDNumber* getGazeOriginLeftYValue() { return ui->gazeOriginLeftEyeYValue; }
  QLCDNumber* getGazeOriginLeftZValue() { return ui->gazeOriginLeftEyeZValue; }
  QLCDNumber* getGazeOriginRightXValue() { return ui->gazeOriginRightEyeXValue; }
  QLCDNumber* getGazeOriginRightYValue() { return ui->gazeOriginRightEyeYValue; }
  QLCDNumber* getGazeOriginRightZValue() { return ui->gazeOriginRightEyeZValue; }

private slots:
  void onStartThreadButtonToggled(bool value);
  void onStartTrackingButtonToggled(bool value);

private:
  Ui::QTobiiDevTrackWindow *ui;

};
} // namespace qtobii

#endif // QTOBII_DEV_TRACK_H
