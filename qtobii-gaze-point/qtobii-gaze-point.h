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

#ifndef QTOBIIGAZEPOINT_H
#define QTOBIIGAZEPOINT_H

#include "qtobii-gaze-point_global.h"
#include "qtobii-plugin-interface.h"
#include <tobii_streams.h>
#include <QObject>
#include <QString>

namespace qtobii {
class QTOBIIGAZEPOINTSHARED_EXPORT QTobiiGazePoint
    : public QObject, public QTobiiPlugin<tobii_gaze_point_callback_t, void*>
{

  Q_OBJECT
  Q_PLUGIN_METADATA(IID "de.dlqx.qtobiiplugin")
  Q_INTERFACES(QTobiiPlugin)

public:
  QTobiiGazePoint();

  virtual QString getDescription() override;

};
} // namespace qtobii

#endif // QTOBIIGAZEPOINT_H
