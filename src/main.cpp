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

#include "qtobii-api.h"
#include "qtobii-api-exception.h"
#include "qtobii-dev-track.h"
#include "qtobii-exit.h"
#include "qtobii-logger.h"
#include "qtobii-tracking-manager.h"
#include <QApplication>
#include <QMessageBox>
#include <QThread>

using namespace qtobii;

int main(int argc, char* argv[]) {

  QApplication app(argc, argv);
  int result = QTobiiExit::NORMAL;
  QTobiiDevTrack* devTrack = new QTobiiDevTrack();
  QTobiiLogger* logger = new QTobiiLogger(devTrack);

  QTobiiApi* api = nullptr;
  QTobiiTrackingManager* manager = nullptr;

  try {
    api = new QTobiiApi(logger, devTrack);
    manager = new QTobiiTrackingManager(api, logger, devTrack);

    devTrack->show();
    result = app.exec();
  } catch (QTobiiApiException& e) {
    QString lastMessage(QString::fromStdString(e.what()));
    logger->debug(QString("Last Message from API: %1").arg(lastMessage));
    QMessageBox::critical(devTrack, "Error", lastMessage, QMessageBox::Ok);

    result = QTobiiExit::API_EXCEPTION;
  } catch (std::exception& e) {
    logger->debug(QString::fromLatin1(e.what()));

    result = QTobiiExit::GENERIC_EXCEPTION;
  }

  if (manager != nullptr) {
    delete manager;
    manager = nullptr;
  }

  if (api != nullptr) {
    if (api->getLastResult()->isError()) {
      result = QTobiiExit::UNKNOWN_ERROR;
    }

    delete api;
    api = nullptr;
  }

  if (devTrack != nullptr) {
    delete devTrack;
    devTrack = nullptr;
  }

  return result;
}
