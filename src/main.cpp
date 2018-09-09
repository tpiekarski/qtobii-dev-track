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
#include <memory>
#include <QApplication>
#include <QMessageBox>
#include <QThread>

int main(int argc, char* argv[]) {

  using namespace qtobii;
  using std::unique_ptr;
  using std::shared_ptr;

  QApplication app(argc, argv);
  int result = QTobiiExit::NORMAL;

  shared_ptr<QTobiiDevTrack> devTrack(new QTobiiDevTrack());
  shared_ptr<QTobiiLogger> logger(new QTobiiLogger(devTrack));

  try {
    shared_ptr<QTobiiApi> api(new QTobiiApi(logger, devTrack));
    unique_ptr<QTobiiTrackingManager> manager(new QTobiiTrackingManager(api, logger, devTrack));

    devTrack->show();
    result = app.exec();
  } catch (QTobiiApiException& e) {
    QString lastMessage(QString::fromStdString(e.what()));
    logger->debug(QString("Last Message from API: %1").arg(lastMessage));
    QMessageBox::critical(devTrack.get(), "Error", lastMessage, QMessageBox::Ok);

    result = QTobiiExit::API_EXCEPTION;
  } catch (std::exception& e) {
    logger->debug(QString::fromLatin1(e.what()));

    result = QTobiiExit::GENERIC_EXCEPTION;
  }

  return result;
}
