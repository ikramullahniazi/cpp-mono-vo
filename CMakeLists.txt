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
	${OpenCV_INCLUDE_DIRS}
	${GTSAM_INCLUDE_DIR}
	${YAML_CPP_INCLUDE_DIR}
	)

add_library( ${PROJECT_NAME}
  src/FeatureTracker.cpp
  src/Camera.cpp
  src/Map.cpp
	)

add_executable(${PROJECT_NAME}-demo src/demo.cpp)

target_link_libraries( ${PROJECT_NAME}-demo
	${PROJECT_NAME}
	${OpenCV_LIBRARIES}
	${GTSAM_LIBRARIES}
	)

