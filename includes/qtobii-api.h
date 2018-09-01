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

#ifndef QTOBIIDEVICE_H
#define QTOBIIDEVICE_H

#include "qtobii-dev-track.h"
#include "qtobii-result.h"
#include <QObject>
#include <QString>
#include <QVector>
#include <tobii.h>

namespace qtobii {
class QTobiiApi : public QObject {

  Q_OBJECT

public:
  explicit QTobiiApi(QObject* parent = nullptr);
  ~QTobiiApi();

  void setup(tobii_error_t result);
  QTobiiResult* QTobiiApi::call(tobii_error_t error);

  tobii_device_t* getDevice() { return device; }
  QTobiiResult* getLastResult() { return results.last(); }
  QString getUrl() { return url; }
  QString getVersion();

private:
  tobii_api_t* api;
  tobii_device_t* device;
  tobii_version_t* version;

  QTobiiDevTrack* devTrack;
  QVector<QTobiiResult*> results;
  QString url;

  static void deviceReceiver(const char* url, void* userData);

};
} // namespace qtobii

#endif // QTOBIIDEVICE_H
