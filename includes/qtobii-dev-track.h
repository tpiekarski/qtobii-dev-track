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

// Forward declaration
namespace Ui { class QTobiiDevTrackWindow; }

namespace qtobii {
class QTobiiDevTrack : public QMainWindow {

  Q_OBJECT

public:
  explicit QTobiiDevTrack(QWidget *parent = nullptr);
  ~QTobiiDevTrack();

  QTobiiTrackingMode getTrackingMode();

  QPushButton* getStartThreadButton();
  QPushButton* getStartTrackingButton();
  QPlainTextEdit* getDataLog();
  QPlainTextEdit* getMessageLog();

  QLCDNumber* getGazePointXValue();
  QLCDNumber* getGazePointYValue();

  QLCDNumber* getGazeOriginLeftXValue();
  QLCDNumber* getGazeOriginLeftYValue();
  QLCDNumber* getGazeOriginLeftZValue();
  QLCDNumber* getGazeOriginRightXValue();
  QLCDNumber* getGazeOriginRightYValue();
  QLCDNumber* getGazeOriginRightZValue();

private slots:
  void onStartThreadButtonToggled(bool value);
  void onStartTrackingButtonToggled(bool value);

private:
  Ui::QTobiiDevTrackWindow *ui;

};
} // namespace qtobii

#endif // QTOBII_DEV_TRACK_H
