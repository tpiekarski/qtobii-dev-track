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

#ifndef QTOBII_TRACKING_INTERFACE_H
#define QTOBII_TRACKING_INTERFACE_H

#include "qtobii-api.h"
#include "qtobii-result.h"

namespace qtobii {
class QTobiiSubscriptionInterface {

public:
  QTobiiSubscriptionInterface(QTobiiApi* api) : m_api(api), m_result(nullptr), m_tracking(true) {}
  virtual ~QTobiiSubscriptionInterface() { /* Defined to make sure all destructors will be called */ }

  virtual void subscribe() = 0;
  virtual void unsubscribe() = 0;

protected:
  QTobiiApi* m_api;
  QTobiiResult* m_result;
  bool m_tracking;

};
} // namespace qtobii

#endif
