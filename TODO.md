QTobiiDevTrack::Todo
--

## Development
- [ ] Add a more reasonable error handling
- [ ] Add a struct for exit codes
- [ ] Add an about dialog
- [ ] Add to gaze point tracking denormalization of coordinates
- [ ] Draft and add a generic interface for following tracking implementations
- [ ] Extend QTobiiData with templates for storing the data received by callback
- [ ] Implement Eye Position tracking, approximation and data display
- [ ] Implement Gaze Origin tracking, approximation and data display
- [ ] Implement Gaze Point tracking, approximation and data display
- [ ] Implement Head Position tracking, approximation and data display
- [ ] Implement reconnection method
- [ ] Implement User Presence tracking and data display
- [x] Add a logger for singla/slot-based logging (instead of using QTobiiDevTrack)
- [x] Add exception for failing loading and/or casting plugins
- [x] Check and enable/disable buttons appropriately for starting/stopping thread and tracking
- [x] Consider to introduce a generic logging interface
- [x] Create and prepare structure for plug-able tracking
- [x] Define a common plugin for all tracking subscriptions from SDK
- [x] Implement a plugin loading mechanism and test within a ground zero
- [x] Implement toggling button to start/stop tracking
- [x] Implement toggling button to start/stop tracking thread
- [x] Integrate Tobii Stream Engine API
- [x] Introduce subdirs for qmake and put final build files into one directory
- [x] Setup API and initialize device
- [x] Start tracking engine in a separate thread

## Documentation
- [ ] Write more detailed README, describing requirements, build process and features
- [ ] Write some description of tracking (gaze, eyes and head) in general
- [x] Add license and license headers
- [x] Add screenshots
- [x] Write a first draft README, explaining utility, showing planed features and status tracking

## Development Improvements
- [ ] Clean present code base
- [ ] Hunt for leaking memory
- [ ] Pass reference arguments instead of pointers all over the place 

## Bugs
- [ ] Check and fix segfaults when trying to restart thread
