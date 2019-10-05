# cpp-mono-vo
Implementing a monocular visual odometry pipeline

## Dependencies

* OpenCV 4.1.0

Note: Plans are in the works to use yaml-cpp for configuration files and GTSAM 4.0 for back end optimization.

Note: Right now, I stylistically prefer to not modify my input variables, and instead generate new output ones. This is probably less efficient than modifying in-place, so a change may be coming. I will not be prematurely optimizing, though.
