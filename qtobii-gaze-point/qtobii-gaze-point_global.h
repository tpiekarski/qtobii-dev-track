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

#ifndef QTOBIIGAZEPOINT_GLOBAL_H
#define QTOBIIGAZEPOINT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTOBIIGAZEPOINT_LIBRARY)
#  define QTOBIIGAZEPOINTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTOBIIGAZEPOINTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QTOBIIGAZEPOINT_GLOBAL_H
