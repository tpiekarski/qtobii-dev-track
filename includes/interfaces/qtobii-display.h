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

#ifndef QTOBIIDISPLAY_H
#define QTOBIIDISPLAY_H

namespace qtobii {
template <class D, class P>
class QTobiiDisplayInterface {

public:
  QTobiiDisplayInterface(D device) : m_device(device) {}
  virtual ~QTobiiDisplayInterface() { /* Defined to make sure all destructors will be called */ }

  virtual void display(const P& payload) = 0;

protected:
  D m_device;

};
} // namespace qtobii

#endif // QTOBIIDISPLAY_H
