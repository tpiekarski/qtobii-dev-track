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

#include "qtobii-logger.h"
#include <QDebug>

namespace qtobii {

void QTobiiLogger::debug(const QString& message) {
  write(MessageType::DEBUG, message);
}

void QTobiiLogger::data(const QString& message) {
  write(MessageType::DATA, message);
}

void QTobiiLogger::log(const QString& message) {
  write(MessageType::MESSAGE, message);
}

void QTobiiLogger::write(const MessageType& type, const QString& message) {
  if (message.isEmpty()) {
    return;
  }

  switch (type) {
    case MessageType::DATA:
      m_devTrack->getDataLog()->appendPlainText(message);
      break;
    case MessageType::MESSAGE:
      m_devTrack->getMessageLog()->appendPlainText(message);
      break;
    case MessageType::DEBUG:
      qDebug() << message;
      break;
  }
}

} // namespace qtobii

