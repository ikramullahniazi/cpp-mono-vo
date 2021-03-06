cmake_minimum_required(VERSION 3.0)

project(MonoVO)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug)
ENDIF()

MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -march=native -std=c++11 -g")

find_package(OpenCV 4.0.0 REQUIRED)

find_package(GTSAM REQUIRED)

#[[
find_package(GTSAMCMakeTools)
include(GtsamMakeConfigFile)
include(GtsamBuildTypes)
include(GtsamTesting)
]]

find_package(yaml-cpp REQUIRED)

include_directories(
	${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/include/Estimator
  ${PROJECT_SOURCE_DIR}/include/FeatureTracker
	${PROJECT_SOURCE_DIR}/include/Optimizer
	${PROJECT_SOURCE_DIR}/include/Utils
  ${PROJECT_SOURCE_DIR}/include/Detector
  ${PROJECT_SOURCE_DIR}/include/Detector/Detectors
  ${PROJECT_SOURCE_DIR}/include/Tracker
  ${PROJECT_SOURCE_DIR}/include/Tracker/Trackers
	${OpenCV_INCLUDE_DIRS}
	${GTSAM_INCLUDE_DIR}
	${YAML_CPP_INCLUDE_DIR}
	)

add_library( ${PROJECT_NAME}
  src/Estimator/Estimator.cpp
  src/FeatureTracker/FeatureTracker.cpp
  src/Detector/Detector.cpp
  src/Detector/Detectors/DefaultDetector.cpp
  src/Tracker/Tracker.cpp
  src/Tracker/Trackers/DefaultTracker.cpp
  # Utils
  src/Utils/Camera.cpp
  src/Utils/Feature.cpp
  src/Utils/Frame.cpp
  src/Utils/ImageGenerator.cpp
  src/Utils/Landmark.cpp
  src/Utils/Map.cpp
  src/Utils/Pose.cpp
	)

add_executable(${PROJECT_NAME}-demo src/demo.cpp)

target_link_libraries( ${PROJECT_NAME}-demo
	${PROJECT_NAME}
	${OpenCV_LIBRARIES}
	${GTSAM_LIBRARIES}
	)

add_executable(testing src/testing.cpp)

target_link_libraries( testing
	${PROJECT_NAME}
	${OpenCV_LIBRARIES}
	${GTSAM_LIBRARIES}
	)

# For some reason, adding more than one causes compiler errors
add_executable(detector_example examples/Detector/example_Detector.cpp)

target_link_libraries(detector_example
  ${PROJECT_NAME}
  ${OpenCV_LIBRARIES}
  ${GTSAM_LIBRARIES}
  )
