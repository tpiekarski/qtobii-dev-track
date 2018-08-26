#
# Project:   QTobiiDevTrack - Utility for discovering, testing and developing eye and gaze tracking
# Github:    https://github.com/tpiekarski/qtobii-dev-track
# Copyright: (c) 2018 Thomas Piekarski <t.piekarski@deloquencia.de>
# License:   Mozilla Public License, v. 2.0
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
# If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

QT -= gui
TARGET = qtobii-gaze-point
TEMPLATE = lib
CONFIG += plugin
DEFINES += QTOBIIGAZEPOINT_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

include(../tobii-stream-sdk.pri)

SOURCES += \
    qtobii-gaze-point.cpp

HEADERS += \
    qtobii-gaze-point.h \
    qtobii-gaze-point_global.h \
    ../qtobii-plugin-interface/qtobii-plugin-interface.h

DISTFILES += \
    LICENSE \
    ../README.md \
    ../TODO.md \
    ../.gitignore \
    ../tobii-stream-sdk.pri
