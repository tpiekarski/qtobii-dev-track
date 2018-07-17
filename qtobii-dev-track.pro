QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtobii-dev-track
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    qtobii-dev-track.cpp

HEADERS += \
    qtobii-dev-track.h

FORMS += \
    qtobii-dev-track-window.ui

RESOURCES += \
    assets.qrc
