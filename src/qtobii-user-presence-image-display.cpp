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

#include "qtobii-user-presence-image-display.h"

namespace qtobii {

void QTobiiUserPresenceImageDisplay::display(const tobii_user_presence_status_t& payload) {
  QString image = QString::fromLatin1(IMAGE_USER_DEFAULT);

  switch (payload) {
  case TOBII_USER_PRESENCE_STATUS_AWAY:
    image = QString::fromLatin1(IMAGE_USER_AWAY);
    break;

  case TOBII_USER_PRESENCE_STATUS_PRESENT:
    image = QString::fromLatin1(IMAGE_USER_PRESENT);
    break;

  case TOBII_USER_PRESENCE_STATUS_UNKNOWN:
    image = QString::fromLatin1(IMAGE_USER_UNKNOWN);
    break;
  }

  m_device->getUserPresenceImageLabel()->setPixmap(QPixmap(image));
}

void QTobiiUserPresenceImageDisplay::displayUserPresence(const tobii_user_presence_status_t& payload) {
  display(payload);
}

void QTobiiUserPresenceImageDisplay::resetUserPresence() {
  m_device->getUserPresenceImageLabel()->setPixmap(QString::fromLatin1(IMAGE_USER_DEFAULT));
}

} // namespace qtobii
