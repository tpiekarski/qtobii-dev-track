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

#ifndef QTOBIIRESULT_H
#define QTOBIIRESULT_H

#include <QObject>
#include <QString>
#include <tobii/tobii.h>

namespace qtobii {
class QTobiiResult : public QObject {

  Q_OBJECT

public:
  explicit QTobiiResult(tobii_error_t error, QObject* parent = nullptr) : QObject(parent), m_error(error) {}
  QTobiiResult(const QTobiiResult&) = default;
  QTobiiResult(QTobiiResult&&) = default;

  bool isError() { return (m_error != TOBII_ERROR_NO_ERROR); }
  tobii_error_t getError() { return m_error; }
  QString getMessage() { return QString::fromLatin1(tobii_error_message(m_error)); }

private:
  tobii_error_t m_error;

};
} // namespace qtobii

#endif // QTOBIIRESULT_H
