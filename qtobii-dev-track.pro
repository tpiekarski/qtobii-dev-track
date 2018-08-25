#
# Project:   QTobiiDevTrack - Utility for discovering, testing and developing eye and gaze tracking
# Github:    https://github.com/tpiekarski/qtobii-dev-track
# Copyright: (c) 2018 Thomas Piekarski <t.piekarski@deloquencia.de>
# License:   Mozilla Public License, v. 2.0
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
# If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtobii-dev-track
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

include(tobii-stream-sdk.pri)

SOURCES += \
    main.cpp \
    qtobii-dev-track.cpp

HEADERS += \
    qtobii-dev-track.h

FORMS += \
    qtobii-dev-track-window.ui

RESOURCES += \
    assets.qrc

DISTFILES += \
    LICENSE \
    README.md \
    TODO.md \
    images/screenshot.png \
    tobii-stream-sdk.pri
