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

#include "qtobii-logger.h"
#include "qtobii-result.h"
#include <QObject>
#include <QString>
#include <QVector>
#include <tobii/tobii.h>

namespace qtobii {
class QTobiiApi : public QObject {

  Q_OBJECT

public:
  explicit QTobiiApi(QTobiiLogger* logger, QObject* parent = nullptr);
  QTobiiApi(const QTobiiApi&) = default;
  QTobiiApi(QTobiiApi &&) = default;
  ~QTobiiApi();

  QTobiiResult* call(tobii_error_t error);

  tobii_device_t* getDevice() { return m_device; }
  QTobiiResult* getLastResult() { return m_results.last(); }
  QTobiiLogger* getLogger() { return m_logger; }
  QString getUrl() { return m_url; }
  QString getVersion();

private:
  tobii_api_t* m_api;
  tobii_device_t* m_device;
  tobii_version_t* m_version;
  QTobiiLogger* m_logger;
  QString m_url;

  QVector<QTobiiResult*> m_results;

  static void deviceReceiver(const char* url, void* data);
  void setup(tobii_error_t error);

};
} // namespace qtobii

#endif // QTOBIIDEVICE_H
