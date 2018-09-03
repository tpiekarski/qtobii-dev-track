QTobiiDevTrack
---
*Future utility for discovering, testing and developing Eye and Gaze Tracking with [Qt](https://www.qt.io/),
[Tobii Stream Engine API](https://developer.tobii.com/consumer-eye-trackers/stream-engine/) and [Tobii Eye Tracking Device](https://tobiigaming.com/).*

## Development
This utility is in very early development, see the [TODO](https://github.com/tpiekarski/qtobii-dev-track/blob/master/TODO.md).
The tracking of the gaze point is already implemented, for further progress please see [Features, Progress](#progress).

## Requirements
* Tobii Eye Tracking Device (Developed and tested with [Tobii Eye Tracker 4C](https://tobiigaming.com/product/tobii-eye-tracker-4c/))
* Microsoft Windows 10
* [Visual Studio](https://visualstudio.microsoft.com/) (tested) or [MinGW](http://mingw.org/) (not tested)
* Qt 5.10.x

## Building
### Visual Studio
To compile and link the application without a Visual Studio Solution and Projects, but with its toolchain configure the CLI environment with vcvarsall, where [product] is Community, Professional, etc., [YYYY] the version of VS 2015/2017/etc. and [target] is either x86 or x64.
```
"C:\Program Files (x86)\Microsoft Visual Studio\[YYYY]\[product]\VC\Auxiliary\Build\vcvarsall.bat" [target]
```
Inside this environment and with the variables mentioned below set up, run qmake and nmake:
```
qmake qtobii-dev-track.pro
nmake [debug|release]
```

### MinGW
To compile and link the application with MinGW run:
```
qmake qtobii-dev-track.pro
mingw32-make
```

### Environment Variables
Variable|Description
---|---
TOBII_STREAM_SDK|Path to the directory containing Tobii Stream SDK

## Features
### Screenshot
![Screenshot of QTobiiDevTrack](images/screenshot.png?raw=true "Screenshot of QTobiiDevTrack")

### Progress
#|Tracker|Description|Status
---|---|---|---
1.|Gaze Point|Normalized X/Y-Tracking of gaze at the screen|done
2.|Gaze Point|Denormalized X/Y-Tracking of gaze at the screen|todo
3.|Gaze Origin|X/Y/Z-Tracking of gaze origin for each eye|todo
4.|Eye Position|X/Y/Z-Tracking of position for each eye|todo
5.|User Presence|Boolean for tracking if user is present|todo
6.|Head Position|X/Y/Z-Tracking of head position and rotation|todo


