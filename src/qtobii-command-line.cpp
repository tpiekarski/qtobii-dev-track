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

#include "qtobii-command-line.h"
#include <QCommandLineOption>

namespace qtobii {

QTobiiCommandLine::QTobiiCommandLine(const QStringList& arguments, QObject* parent)
  : QObject(parent), m_parser(new QCommandLineParser())
{
  m_parser->setApplicationDescription("Utility for discovering, testing and developing Eye and Gaze Tracking");
  m_parser->addHelpOption();
  m_parser->addVersionOption();

  const QString processCallbackIntervallOptionName = QString::fromLatin1(PROCESS_CALLBACK_INTERVALL_OPTION);
  QCommandLineOption processCallbackInterval(
    processCallbackIntervallOptionName,
    "Interval for processing callbacks in miliseconds.",
    processCallbackIntervallOptionName,
    QString::number(PROCESS_CALLBACK_DEFAULT_INTERVALL)
  );

  m_parser->addOption(processCallbackInterval);
  m_parser->process(arguments);

  bool result = false;
  int value = m_parser->value(processCallbackIntervallOptionName).toInt(&result);
  m_processCallbackIntervall = (!result || value < 0) ? PROCESS_CALLBACK_DEFAULT_INTERVALL : value;
}

} // namespace qtobii
