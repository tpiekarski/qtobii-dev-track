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

#ifndef QTOBIILOGGER_H
#define QTOBIILOGGER_H

#include "interfaces/qtobii-logging.h"
#include "qtobii-dev-track.h"
#include <QObject>
#include <QString>

namespace qtobii {
class QTobiiLogger : public QObject, QTobiiLoggingInterface {

  Q_OBJECT

public:
  explicit QTobiiLogger(QTobiiDevTrack* devTrack) : QObject(devTrack), devTrack(devTrack) {}

public slots:
  void debug(QString message) override;
  void data(QString message) override;
  void log(QString message) override;

protected:
  void write(MessageType type, QString message);

private:
  QTobiiDevTrack* devTrack;

};
} // namespace qtobii

#endif // QTOBIILOGGER_H
