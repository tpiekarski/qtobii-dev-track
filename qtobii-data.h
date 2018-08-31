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

#ifndef QTOBIIDATA_H
#define QTOBIIDATA_H

#include <QObject>

namespace qtobii {
class QTobiiData : public QObject {

  Q_OBJECT

public:
  explicit QTobiiData(QObject *parent = nullptr) : QObject(parent) {}
  void send(QString message) {
    emit transmit(message);
  }

signals:
  void transmit(QString message);

};
} // namespace tobii

#endif // QTOBIIDATA_H
