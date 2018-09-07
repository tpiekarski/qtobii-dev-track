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
  explicit QTobiiDevTrack(QWidget* parent = nullptr);
  QTobiiDevTrack(const QTobiiDevTrack&) = default;
  QTobiiDevTrack(QTobiiDevTrack&&) = default;
  ~QTobiiDevTrack();

  QTobiiTrackingMode getTrackingMode();

  QPushButton* getStartThreadButton() { return m_ui->startThreadButton; }
  QPushButton* getStartTrackingButton() { return m_ui->startTrackingButton; }
  QPlainTextEdit* getDataLog() { return m_ui->dataLog; }
  QPlainTextEdit* getMessageLog() { return m_ui->messageLog; }

  QLCDNumber* getGazePointXValue() { return m_ui->gazePointXValue; }
  QLCDNumber* getGazePointYValue() { return m_ui->gazePointYValue; }

  QLCDNumber* getGazeOriginLeftXValue() { return m_ui->gazeOriginLeftEyeXValue; }
  QLCDNumber* getGazeOriginLeftYValue() { return m_ui->gazeOriginLeftEyeYValue; }
  QLCDNumber* getGazeOriginLeftZValue() { return m_ui->gazeOriginLeftEyeZValue; }
  QLCDNumber* getGazeOriginRightXValue() { return m_ui->gazeOriginRightEyeXValue; }
  QLCDNumber* getGazeOriginRightYValue() { return m_ui->gazeOriginRightEyeYValue; }
  QLCDNumber* getGazeOriginRightZValue() { return m_ui->gazeOriginRightEyeZValue; }
  QLCDNumber* getEyePositionLeftXValue() { return m_ui->eyePositionLeftEyeXValue; }
  QLCDNumber* getEyePositionLeftYValue() { return m_ui->eyePositionLeftEyeYValue; }
  QLCDNumber* getEyePositionLeftZValue() { return m_ui->eyePositionLeftEyeZValue; }
  QLCDNumber* getEyePositionRightXValue() { return m_ui->eyePositionRightEyeXValue; }
  QLCDNumber* getEyePositionRightYValue() { return m_ui->eyePositionRightEyeYValue; }
  QLCDNumber* getEyePositionRightZValue() { return m_ui->eyePositionRightEyeZValue; }

private slots:
  void onStartThreadButtonToggled(bool value);
  void onStartTrackingButtonToggled(bool value);

private:
  Ui::QTobiiDevTrackWindow* m_ui;

};
} // namespace qtobii

#endif // QTOBII_DEV_TRACK_H
