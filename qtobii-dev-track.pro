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
CONFIG += c++14
CONFIG(release, debug|release) { DEFINES += QT_NO_DEBUG_OUTPUT }
INCLUDEPATH *= includes

include(msvc-workaround.pri)
include(tobii-stream-sdk.pri)

SOURCES += \
    src/main.cpp \
    src/qtobii-api.cpp \
    src/qtobii-dev-track.cpp \
    src/qtobii-gaze-point.cpp \
    src/qtobii-tracker.cpp \
    src/qtobii-tracking-manager.cpp \
    src/qtobii-logger.cpp

HEADERS += \
    includes/qtobii-api-exception.h \
    includes/qtobii-api.h \
    includes/qtobii-data.h \
    includes/qtobii-dev-track.h \
    includes/qtobii-gaze-point.h \
    includes/qtobii-result.h \
    includes/qtobii-tracker.h \
    includes/qtobii-tracking-manager.h \
    includes/qtobii-logger.h \
    includes/qtobii-api-exception.h \
    includes/qtobii-api.h \
    includes/qtobii-data.h \
    includes/qtobii-dev-track.h \
    includes/qtobii-gaze-point.h \
    includes/qtobii-logger.h \
    includes/qtobii-result.h \
    includes/qtobii-tracker.h \
    includes/qtobii-tracking-manager.h \
    includes/interfaces/qtobii-logging.h \
    includes/interfaces/qtobii-subscription.h \
    includes/qtobii-data-messenger.h \
    includes/qtobii-exchange-container.h

FORMS += \
    forms/qtobii-dev-track-window.ui

RESOURCES += \
    assets/assets.qrc

DISTFILES += \
    LICENSE \
    README.md \
    TODO.md

