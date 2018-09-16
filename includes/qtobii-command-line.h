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

#ifndef QTOBIICOMMANDLINE_H
#define QTOBIICOMMANDLINE_H

#include <memory>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QObject>
#include <QStringList>

namespace qtobii {

using std::unique_ptr;

class QTobiiCommandLine : public QObject {

  Q_OBJECT

public:
  explicit QTobiiCommandLine(const QStringList& arguments, QObject* parent = nullptr);

  int getProcessCallbackIntervall() { return m_processCallbackIntervall; }

private:
  static constexpr int PROCESS_CALLBACK_DEFAULT_INTERVALL   = 100;
  static constexpr char PROCESS_CALLBACK_INTERVALL_OPTION[] = "process-callback-intervall";

  unique_ptr<QCommandLineParser> m_parser;
  int m_processCallbackIntervall;

};
} // namespace qtobii

#endif // QTOBIICOMMANDLINE_H
