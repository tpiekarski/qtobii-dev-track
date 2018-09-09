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
#include <memory>
#include <QObject>
#include <QString>

namespace qtobii {

using std::shared_ptr;

class QTobiiLogger : public QObject, QTobiiLoggingInterface {

  Q_OBJECT

public:
  explicit QTobiiLogger(shared_ptr<QTobiiDevTrack> devTrack) : QObject(devTrack.get()), m_devTrack(devTrack) {}
  QTobiiLogger(const QTobiiLogger&) = default;
  QTobiiLogger(QTobiiLogger&&) = default;

public slots:
  void debug(const QString& message) override;
  void data(const QString& message) override;
  void log(const QString& message) override;

protected:
  void write(const MessageType& type, const QString& message);

private:
  shared_ptr<QTobiiDevTrack> m_devTrack;

};
} // namespace qtobii

#endif // QTOBIILOGGER_H
