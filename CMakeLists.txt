cmake_minimum_required(VERSION 3.0)

project(MonoVO)

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
  src/Tracker/Tracker.cpp
  src/Utils/Camera.cpp
  src/Utils/Map.cpp
  src/Utils/Feature.cpp
  src/Utils/Landmark.cpp
	)

add_executable(${PROJECT_NAME}-demo src/demo.cpp)

target_link_libraries( ${PROJECT_NAME}-demo
	${PROJECT_NAME}
	${OpenCV_LIBRARIES}
	${GTSAM_LIBRARIES}
	)

