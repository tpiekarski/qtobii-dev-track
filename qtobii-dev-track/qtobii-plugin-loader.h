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

#ifndef QTOBIIPLUGINLOADER_H
#define QTOBIIPLUGINLOADER_H

#include "qtobii-plugin-interface.h"
#include <QDir>
#include <QFileInfo>
#include <QObject>
#include <tobii_streams.h>

namespace qtobii {
class QTobiiPluginLoader : public QObject {

  Q_OBJECT

public:
  explicit QTobiiPluginLoader(QObject* parent = nullptr) : QObject(parent) {}
  auto getGazePointPlugin() { return gazePointPlugin; }
  void load(QDir directory);

private:
  QTobiiPlugin<tobii_gaze_point_callback_t, void*>* gazePointPlugin;
  QTobiiPlugin<tobii_gaze_point_callback_t, void*>* loadGazePointPlugin(QFileInfo* pluginFile);

};
} // namespace qtobii

#endif // QTOBIIPLUGINLOADER_H
