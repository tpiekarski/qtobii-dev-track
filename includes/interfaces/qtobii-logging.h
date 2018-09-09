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

#ifndef QTOBIILOGGINGINTERFACE_H
#define QTOBIILOGGINGINTERFACE_H

#include <QObject>
#include <QString>

namespace qtobii {
class QTobiiLoggingInterface {

public:
  virtual ~QTobiiLoggingInterface() {
    // Only defined to make sure all destructors will be called along inheritance.
  }

  enum MessageType {
    DATA,
    DEBUG,
    MESSAGE
  };

public slots:
  virtual void debug(const QString& message) = 0;
  virtual void data(const QString& message) = 0;
  virtual void log(const QString& message) = 0;

};
} // namespace qtobii

#endif // QTOBIILOGGINGINTERFACE_H
