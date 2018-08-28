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

#ifndef QTOBIIGAZEPOINT_H
#define QTOBIIGAZEPOINT_H

#include "qtobii-tracking-interface.h"
#include <QObject>
#include <QPair>
#include <QString>
#include <QVector>

namespace qtobii {
class QTobiiGazePoint : public QObject, public QTobiiTrackingInterface {

  Q_OBJECT

public:
  QTobiiGazePoint();

  //virtual QTobiiResult subscribe(tobii_device_t* device);
  //virtual QTobiiResult unsubscribe(tobii_device_t* device);
  virtual QString getDescription() override;

  QVector<QPair<float, float>> getData() { return data; }
  QPair<float, float> getLastData() { return data.last(); }

private:
  QVector<QPair<float, float>> data;

};
} // namespace qtobii

#endif // QTOBIIGAZEPOINT_H
