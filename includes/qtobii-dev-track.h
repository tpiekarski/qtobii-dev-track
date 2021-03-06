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
#include <QCheckBox>
#include <QLabel>
#include <QLCDNumber>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSize>

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
  QSize getScreenSize() { return m_screenSize; }

  QPushButton* getStartThreadButton() { return m_ui->startThreadButton; }
  QPushButton* getStartTrackingButton() { return m_ui->startTrackingButton; }
  QPlainTextEdit* getDataLog() { return m_ui->dataLog; }
  QPlainTextEdit* getMessageLog() { return m_ui->messageLog; }

  QLCDNumber* getGazePointXValue() { return m_ui->gazePointXValue; }
  QLCDNumber* getGazePointYValue() { return m_ui->gazePointYValue; }
  bool denormalizeGazePoint() { return m_ui->gazePointDenormalizeCheckBox->isChecked(); }

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

  QLCDNumber* getHeadPositionXValue() { return m_ui->headPositionPositionXValue; }
  QLCDNumber* getHeadPositionYValue() { return m_ui->headPositionPositionYValue; }
  QLCDNumber* getHeadPositionZValue() { return m_ui->headPositionPositionZValue; }
  QLCDNumber* getHeadRotationXValue() { return m_ui->headPositionRotationXValue; }
  QLCDNumber* getHeadRotationYValue() { return m_ui->headPositionRotationYValue; }
  QLCDNumber* getHeadRotationZValue() { return m_ui->headPositionRotationZValue; }

  QLabel* getUserPresenceImageLabel() { return m_ui->userPresenceImageLabel; }

  enum XYZ { X = 0, Y = 1, Z = 2 };

private slots:
  void onStartThreadButtonToggled(const bool& value);
  void onStartTrackingButtonToggled(const bool& value);
  void onStartTrackingBoxToggled(const bool& value);

private:
  Ui::QTobiiDevTrackWindow* m_ui;
  QSize m_screenSize;

};
} // namespace qtobii

#endif // QTOBII_DEV_TRACK_H
