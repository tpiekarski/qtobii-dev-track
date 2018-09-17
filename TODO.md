QTobiiDevTrack::Todo
--

## Features
- [ ] Track subscriptions to enable multiple subscriptions instead of disabling other tracking box pages
- [x] Add a logger for signal/slot-based logging (instead of using QTobiiDevTrack)
- [x] Add an enum for exit codes
- [x] Add a way to set the time between processing callbacks (CALLBACK_PROCESS_TIMER)
- [x] Add exception for failing loading and/or casting plugins
- [x] Add manifest file and update description of build process
- [x] Check and enable/disable buttons appropriately for starting/stopping thread and tracking
- [x] Consider introducing a generic logging interface
- [x] Create and prepare structure for plug-able tracking
- [x] Define a common plugin for all tracking subscriptions from SDK
- [x] Disable other tracking tool pages as soon as one tracking is started
- [x] Draft and add a generic interface for following tracking implementations
- [x] Extend QTobiiData with templates for storing the data received by callback
- [x] Find and integrate a package manager to pull in Tobii Stream Engine from nuget (chose [Paket](https://fsprojects.github.io/Paket/index.html))
- [x] Find, check and integrate further static code analysers and code linters (Integrated cppcheck and cppclean)
- [x] Implement a plugin loading mechanism and test within a ground zero
- [x] Implement denormalization of coordinates for gaze point tracking
- [x] Implement Eye Position tracking, approximation and data display
- [x] Implement Gaze Origin tracking, approximation and data display
- [x] Implement Gaze Point tracking, approximation and data display
- [x] Implement Head Position tracking, approximation and data display
- [ ] Implement reconnection method
- [x] Implement toggling button to start/stop tracking
- [x] Implement toggling button to start/stop tracking thread
- [x] Implement User Presence tracking and data display
- [x] Integrate public CI build system like AppVeyor or Travis
- [x] Integrate Tobii Stream Engine API
- [x] Introduce subdirs for qmake and put final build files into one directory
- [x] Pick up transmit signal with tobii_gaze_point_t and finaly display data in QLCDNumber widgets
- [x] Provide Visual Studio Solution/Project files next to qmake project file (description to generate one provided instead)
- [x] Setup API and initialize device
- [x] Start tracking engine in a separate thread
- [x] Transmitting tracking data (tobii_gaze_point_t)
- [x] Update description of build process and mention new package manager
- [x] Use QTimer to slow down the display of tracking data in QLCDNumber (Reducing flickering of display)

## Documentation
- [x] Add license and license headers
- [x] Add screenshots
- [x] Write a first draft README, explaining utility, showing planed features and status tracking
- [x] Write more detailed README, describing requirements, build process and features

## Development Improvements
- [ ] Add a more reasonable error handling
- [ ] Move from C-style array to STL array in extract methods of QTobiiGazePoint and QTobiiGazeOrigin
- [ ] Reduce as much as possible redundant code at tracking and displaying classes
- [x] Check destructors (counting on the compiler to provide default destructors)
- [x] Clean present code base
- [x] Consider to switch to smart pointers
- [x] Hunt for leaking memory
- [x] Migrate QTobiiDisplayInterface to shared pointers to finish transition of QTobiiDevTrack
- [x] Migrate QTobiiSubscriptionInterface to shared pointers to finish transition of QTobiiApi
- [x] Pass reference arguments instead of pointers (and copies) all over the place
- [x] Streamline child constructors of QObject (parent should be always last, default assigned to nullptr)
- [x] Transition to unique and shared pointers (where it is straight-forward, it is done)
- [-] Getting LCDNumberLabels in groups instead of every single one (it's not worth to get them in groups)

## Performance
- [ ] Investigate high CPU load when the tracking thread runs

## Bugs
- [ ] Check and debug unexpected null parameter when disconnection data objects
- [x] Check and fix segfaults when trying to restart thread

