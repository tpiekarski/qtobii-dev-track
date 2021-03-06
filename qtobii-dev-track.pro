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

include(imports/msvc-workaround.pri)
include(imports/tobii-stream-sdk.pri)

SOURCES += \
    src/main.cpp \
    src/qtobii-api.cpp \
    src/qtobii-command-line.cpp \
    src/qtobii-dev-track.cpp \
    src/qtobii-eye-position.cpp \
    src/qtobii-eye-position-lcd-display.cpp \
    src/qtobii-gaze-origin.cpp \
    src/qtobii-gaze-origin-lcd-display.cpp \
    src/qtobii-gaze-point.cpp \
    src/qtobii-gaze-point-lcd-display.cpp \
    src/qtobii-head-position.cpp \
    src/qtobii-head-position-lcd-display.cpp \
    src/qtobii-logger.cpp \
    src/qtobii-tracker.cpp \
    src/qtobii-tracking-manager.cpp \
    src/qtobii-user-presence.cpp \
    src/qtobii-user-presence-image-display.cpp

HEADERS += \
    includes/interfaces/qtobii-display.h \
    includes/interfaces/qtobii-logging.h \
    includes/interfaces/qtobii-subscription.h \
    includes/qtobii-api.h \
    includes/qtobii-api-exception.h \
    includes/qtobii-command-line.h \
    includes/qtobii-data.h \
    includes/qtobii-data-messenger.h \
    includes/qtobii-dev-track.h \
    includes/qtobii-eye-position.h \
    includes/qtobii-eye-position-lcd-display.h \
    includes/qtobii-exchange-container.h \
    includes/qtobii-exit.h \
    includes/qtobii-gaze-origin.h \
    includes/qtobii-gaze-origin-lcd-display.h \
    includes/qtobii-gaze-point.h \
    includes/qtobii-gaze-point-lcd-display.h \
    includes/qtobii-head-position.h \
    includes/qtobii-head-position-lcd-display.h \
    includes/qtobii-logger.h \
    includes/qtobii-result.h \
    includes/qtobii-tracker.h \
    includes/qtobii-tracking-manager.h \
    includes/qtobii-tracking-mode.h \
    includes/qtobii-user-presence.h \
    includes/qtobii-user-presence-image-display.h

FORMS += \
    forms/qtobii-dev-track-window.ui

RESOURCES += \
    assets/assets.qrc

DISTFILES += \
    LICENSE \
    README.md \
    TODO.md

