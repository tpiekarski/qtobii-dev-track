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

#ifndef QTOBIIAPIEXCEPTION_H
#define QTOBIIAPIEXCEPTION_H

#include <exception>
#include <string>

namespace qtobii {

using std::exception;
using std::string;

class QTobiiApiException : public exception {

public:
  QTobiiApiException(string message = "Failed initializing tracking device.") : message(message) {}
  string what() { return message; }

private:
  string message;

};
} // namespace qtobii

#endif // QTOBIIAPIEXCEPTION_H
