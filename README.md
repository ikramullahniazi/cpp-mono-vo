# cpp-mono-vo

This is a monocular visual odometry pipeline I am writing as a personal project.
The purpose of this project is to learn the new OpenCV 4 API as well as practice modern C++; see 
[here](https://github.com/mattboler/matlab-VO) for a repository where I 
implement common visual navigation functions in Matlab.

## Prerequisites

This is written and tested on Ubuntu 18.04.

### Libraries

* OpenCV 4.1.0

## Installation

Clone the repository and

```
mkdir build && cd build
cmake ..
make -j4
```

## Configuration

An Odometry/SLAM system consists of the following components:

* Detector: An object which detects features in incoming images
* Tracker: An object with tracks features from one image into another
* FeatureTracker: An object which manages both a Detector and Tracker to produce measurements of features over time
* Estimator: An object which uses measurements from a FeatureTracker to calculate the motion of the camera
* Optimizer: An object which optimizes a sequence of estimates from the Estimator

An Optimizer is optional, while the others make up the minimum configuration for motion calculation.


