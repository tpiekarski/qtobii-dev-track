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

#ifndef QTOBIIUSERPRESENCEIMAGEDISPLAY_H
#define QTOBIIUSERPRESENCEIMAGEDISPLAY_H

#include "interfaces/qtobii-display.h"
#include "qtobii-dev-track.h"
#include <memory>
#include <QObject>
#include <tobii/tobii_streams.h>

namespace qtobii {

using std::shared_ptr;

class QTobiiUserPresenceImageDisplay
    : public QObject, public QTobiiDisplayInterface<shared_ptr<QTobiiDevTrack>, tobii_user_presence_status_t>
{

  Q_OBJECT

public:
  explicit QTobiiUserPresenceImageDisplay(shared_ptr<QTobiiDevTrack> device, QObject* parent = nullptr)
    : QObject(parent), QTobiiDisplayInterface<shared_ptr<QTobiiDevTrack>, tobii_user_presence_status_t>(device) {}
  QTobiiUserPresenceImageDisplay(const QTobiiUserPresenceImageDisplay&) = default;
  QTobiiUserPresenceImageDisplay(QTobiiUserPresenceImageDisplay&&) = default;

  virtual void display(const tobii_user_presence_status_t& payload) override;

public slots:
  void displayUserPresence(const tobii_user_presence_status_t& payload);
  void resetUserPresence();

private:
  static constexpr char IMAGE_USER_AWAY[]    = ":/assets/user-away.png";
  static constexpr char IMAGE_USER_DEFAULT[] = ":/assets/user-default.png";
  static constexpr char IMAGE_USER_PRESENT[] = ":/assets/user-present.png";
  static constexpr char IMAGE_USER_UNKNOWN[] = ":/assets/user-unknown.png";

};
} // namespace qtobii

#endif // QTOBIIUSERPRESENCEIMAGEDISPLAY_H
