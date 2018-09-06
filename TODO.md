QTobiiDevTrack::Todo
--

## Development
- [ ] Add a more reasonable error handling
- [ ] Add an about dialog
- [ ] Add manifest file and update description of build process
- [ ] Add to gaze point tracking denormalization of coordinates
- [ ] Disable other tracking tool pages as soon one tracking is started
- [ ] Draft and add a generic interface for following tracking implementations
- [ ] Find, check and integrate further static code analysers and code linters
- [ ] Implement Eye Position tracking, approximation and data display
- [ ] Implement Gaze Point tracking, approximation and data display
- [ ] Implement Head Position tracking, approximation and data display
- [ ] Implement reconnection method
- [ ] Implement User Presence tracking and data display
- [ ] Integrate public static code analysis like SonarCloud
- [ ] Move from C-style array to STL array in extract methods of QTobiiGazePoint and QTobiiGazeOrigin
- [ ] Use QTimer to slow down the display of tracking data in QLCDNumber (Reducing flickering of display)
- [ ] Track subscriptions to enable multiple subscriptions instead of disabling other tracking box pages
- [x] Add a logger for signal/slot-based logging (instead of using QTobiiDevTrack)
- [x] Add an enum for exit codes
- [x] Add exception for failing loading and/or casting plugins
- [x] Check and enable/disable buttons appropriately for starting/stopping thread and tracking
- [x] Consider introducing a generic logging interface
- [x] Create and prepare structure for plug-able tracking
- [x] Define a common plugin for all tracking subscriptions from SDK
- [x] Extend QTobiiData with templates for storing the data received by callback
- [x] Find and integrate a package manager to pull in Tobii Stream Engine from nuget (chose [Paket](https://fsprojects.github.io/Paket/index.html))
- [x] Implement a plugin loading mechanism and test within a ground zero
- [x] Implement Gaze Origin tracking, approximation and data display
- [x] Implement toggling button to start/stop tracking
- [x] Implement toggling button to start/stop tracking thread
- [x] Integrate public CI build system like AppVeyor or Travis
- [x] Integrate Tobii Stream Engine API
- [x] Introduce subdirs for qmake and put final build files into one directory
- [x] Pick up transmit signal with tobii_gaze_point_t and finaly display data in QLCDNumber widgets
- [x] Provide Visual Studio Solution/Project files next to qmake project file (description to generate one provided instead)
- [x] Setup API and initialize device
- [x] Start tracking engine in a separate thread
- [x] Transmitting tracking data (tobii_gaze_point_t)
- [x] Update description of build process and mention new package manager

## Documentation
- [ ] Write more detailed README, describing requirements, build process and features
- [ ] Write some description of tracking (gaze, eyes and head) in general
- [x] Add license and license headers
- [x] Add screenshots
- [x] Write a first draft README, explaining utility, showing planed features and status tracking

## Development Improvements
- [ ] Check destructors (few are missing)
- [ ] Consider to switch to smart pointers
- [ ] Hunt for leaking memory
- [ ] Pass reference arguments instead of pointers all over the place
- [ ] Streamline child constructors of QObject (parent should be always last, default assigned to nullptr)
- [x] Clean present code base

## Bugs
- [ ] Check and fix segfaults when trying to restart thread
