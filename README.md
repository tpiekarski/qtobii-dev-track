QTobiiDevTrack
---

[![Build status](https://ci.appveyor.com/api/projects/status/9vnj8neqba8cybmj?svg=true)](https://ci.appveyor.com/project/tpiekarski/qtobii-dev-track)

*Future utility for discovering, testing and developing Eye and Gaze Tracking with [Qt](https://www.qt.io/),
[Tobii Stream Engine Native](https://developer.tobii.com/consumer-eye-trackers/stream-engine/) and
[Tobii Eye Tracking Device](https://tobiigaming.com/).*

## Development
This utility is in very early development, see the [TODO](https://github.com/tpiekarski/qtobii-dev-track/blob/master/TODO.md).
The tracking of the gaze point is already implemented, for further progress please see [Features, Progress](#progress).

## Requirements
* Tobii Eye Tracking Device (Developed and tested with [Tobii Eye Tracker 4C](https://tobiigaming.com/product/tobii-eye-tracker-4c/))
* [Tobii Stream Engine Native](https://www.nuget.org/packages/Tobii.StreamEngine.Native/) 2.2.x.x
* [Qt](https://www.qt.io/download-qt-installer) 5.10.x
* [Paket](https://fsprojects.github.io/Paket/index.html) 5.x
* [Visual Studio](https://visualstudio.microsoft.com/) (tested) or [MinGW](http://mingw.org/) (not tested) 
* Microsoft Windows >= 7 (x86/x64)

## Building

### Dependencies
For managing dependencies Paket is used and the bootstrapper binary executable is included in the directory .paket. 
Before continuing the build process please install all dependencies by running:
```
.paket\paket.exe install
```

### MSBuild
To compile and link the application with MSBuild, but without a Visual Studio Project nor Solution, 
configure the CLI environment with vcvarsall, where [product] is Community, Professional, etc., [YYYY] 
the version of VS 2015/2017/etc. and [target] is either x86 or x64.
```
"C:\Program Files (x86)\Microsoft Visual Studio\[YYYY]\[product]\VC\Auxiliary\Build\vcvarsall.bat" [target]
```
Inside this environment run qmake and nmake to build either a debug or release builds:
```
qmake qtobii-dev-track.pro
nmake [debug|release]
```

### Qt Creator
To compile and link the application inside Qt Creator just open the qtobii-dev-track.pro, run qmake and build it.
When using shadow builds make sure to add one additional build step to copy the packages directory to the build 
directory before running jom. Otherwise linking will fail due to missing tobii_stream_engine.lib.

### Visual Studio
To compile and link the application inside Visual Studio generate a Visual Studio project file with qmake
and then proceed and build the project.
```
qmake -tp vc qtobii-dev-track.pro
```

### MinGW
To compile and link the application with MinGW run:
```
qmake qtobii-dev-track.pro
mingw32-make
```

## Features
### Screenshot
![Screenshot of QTobiiDevTrack](images/screenshot.png?raw=true "Screenshot of QTobiiDevTrack")

### Progress
#|Tracker|Description|Status
---|---|---|---
1.|Gaze Point|Normalized X/Y-Tracking of gaze at the screen|done
2.|Gaze Point|Denormalized X/Y-Tracking of gaze at the screen|todo
3.|Gaze Origin|X/Y/Z-Tracking of gaze origin for each eye|done
4.|Eye Position|X/Y/Z-Tracking of position for each eye|todo
5.|User Presence|Boolean for tracking if user is present|todo
6.|Head Position|X/Y/Z-Tracking of head position and rotation|todo



