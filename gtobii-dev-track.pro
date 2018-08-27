#
# Project:   QTobiiDevTrack - Utility for discovering, testing and developing eye and gaze tracking
# Github:    https://github.com/tpiekarski/qtobii-dev-track
# Copyright: (c) 2018 Thomas Piekarski <t.piekarski@deloquencia.de>
# License:   Mozilla Public License, v. 2.0
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
#

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = \
    qtobii-gaze-point \
    qtobii-dev-track
    
qtobii-dev-track.subdir = qtobii-dev-track
qtobii-gaze-point.subdir = qtobii-gaze-point

qtobii-dev-track.depends = qtobii-gaze-point
