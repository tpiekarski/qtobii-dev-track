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

#ifndef QTOBIIDATACONTAINER_H
#define QTOBIIDATACONTAINER_H

#include "qtobii-data.h"

namespace qtobii {
template <class D, class M>
class QTobiiExchangeContainer {

public:
  QTobiiExchangeContainer(QTobiiData<D>* data, QTobiiData<M>* messages) : m_data(data), m_messages(messages) {}
  QTobiiExchangeContainer(const QTobiiExchangeContainer&) = default;
  QTobiiExchangeContainer(QTobiiExchangeContainer&&) = default;

  QTobiiData<D>* getData() { return m_data; }
  QTobiiData<M>* getMessages() { return m_messages; }

private:
  QTobiiData<D>* m_data;
  QTobiiData<M>* m_messages;

};
} // namespace qtobii

#endif // QTOBIIDATACONTAINER_H
