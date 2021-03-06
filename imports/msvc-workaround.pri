#
# Project:   QTobiiDevTrack - Utility for discovering, testing and developing eye and gaze tracking
# Github:    https://github.com/tpiekarski/qtobii-dev-track
# Copyright: (c) 2018 Thomas Piekarski <t.piekarski@deloquencia.de>
# License:   Mozilla Public License, v. 2.0
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
# If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

win32-msvc* {
    message("Compiling with Microsoft Visual Studio Toolchain, using workaround for qOverload.")
    message("For details see: https://bugreports.qt.io/browse/QTBUG-61667")

    DEFINES += QTOBII_MSVC_QOVERLOAD_WORKAROUND
}
