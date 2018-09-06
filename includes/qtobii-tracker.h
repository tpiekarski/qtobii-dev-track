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
  explicit QTobiiTracker(QObject* parent, QTobiiApi* api) : QObject(parent), m_api(api), m_tracking(DEFAULT_TRACKING) {}
  QTobiiTracker(const QTobiiTracker&) = default;
  QTobiiTracker(QTobiiTracker&&) = default;

public slots:
  void start();
  void stop();

signals:
  void finished();
  void log(QString message);
  void error(QString error);

private:
  static constexpr int DEFAULT_DEVICE = 1;
  static constexpr bool DEFAULT_TRACKING = true;

  QTobiiApi* m_api;
  bool m_tracking;

};
} // namespace qtobii

#endif // QTOBIITRACKER_H
