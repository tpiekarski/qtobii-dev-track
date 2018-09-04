#
# Project:   QTobiiDevTrack - Utility for discovering, testing and developing eye and gaze tracking
# Github:    https://github.com/tpiekarski/qtobii-dev-track
# Copyright: (c) 2018 Thomas Piekarski <t.piekarski@deloquencia.de>
# License:   Mozilla Public License, v. 2.0
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
# If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

TOBII_STREAM_SDK = packages\Tobii.StreamEngine.Native\build\native
TOBII_STREAM_INCLUDE = $$sprintf("%1\include", $$TOBII_STREAM_SDK)

INCLUDEPATH *= $$TOBII_STREAM_INCLUDE

equals(QT_ARCH, "x86_64") { ARCH = x64 } else { ARCH = x86 }

TOBII_STREAM_LIB = $$quote($$sprintf("%1\lib\%2\tobii_stream_engine", $$TOBII_STREAM_SDK, $$ARCH))
TOBII_STREAM_LIB ~= s@\\\@/

Debug: { LIBS *= -l$$TOBII_STREAM_LIB }
Release: { LIBS *= -l$$TOBII_STREAM_LIB }
