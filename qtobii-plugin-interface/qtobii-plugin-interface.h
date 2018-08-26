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

#ifndef QTOBII_PLUGIN_INTERFACE_H
#define QTOBII_PLUGIN_INTERFACE_H

#include "qtobii-device.h"
#include "qtobii-result.h"
#include <QString>

class QTobiiPlugin;

#define QTOBII_PLUGIN_ID "de.dlqx.qtobiiplugin"
Q_DECLARE_INTERFACE(QTobiiPlugin, QTOBII_PLUGIN_ID)

namespace qtobii {
template <class C, class D> class QTobiiPlugin {

public:
  virtual ~QTobiiPlugin() {
    // Only defined to make sure all destructors will be called along inheritance.
  }

  virtual QTobiiResult subscribe(QTobiiDevice* device, C callback, D data) = 0;
  virtual QTobiiResult unsubscribe(QTobiiDevice* device) = 0;

  virtual C getCallback() = 0;
  virtual D getData() = 0;

  virtual QString getDescription() = 0;

};
} // namespace qtobii
#endif
