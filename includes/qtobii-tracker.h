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

#ifndef QTOBIITRACKER_H
#define QTOBIITRACKER_H

#include "qtobii-api.h"
#include <QObject>
#include <QString>

namespace qtobii {
class QTobiiTracker : public QObject {

  Q_OBJECT

public:
  explicit QTobiiTracker(QTobiiApi* api) : api(api), tracking(true) {}

public slots:
  void start();
  void stop();

signals:
  void finished();
  void log(QString message);
  void error(QString error);

private:
  QTobiiApi* api;
  bool tracking;

};
} // namespace qtobii

#endif // QTOBIITRACKER_H
