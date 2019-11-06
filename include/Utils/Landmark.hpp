#ifndef LANDMARK_HPP_INCLUDE
#define LANDMARK_HPP_INCLUDE

#include <vector>
#include <map>

#include <opencv2/core.hpp>

#include "Utils/Feature.hpp" // Features are measurments of landmarks

// This class represents 3D landmarks 

class Landmark {
  public:
    // ------------
    // Constructors
    // ------------
    Landmark();
    Landmark(
        int id,
        cv::Point3f coords);
    Landmark(
        int id,
        cv::Point3f coords, 
        std::vector<Feature> observations);
    
    // ---------
    // Functions
    // ---------
    
    // ----
    // Data
    // ----

    // Unique ID
    int id;

    // Location relative to origin of map
    cv::Point3f coords;

    // Keep track of all observations of this landmark
    std::vector<Feature> observations;
};

// Map landmark ID to landmark object
typedef std::map<int, Landmark> landmark_map_t;

typedef struct LandmarkMapAsVectors {
  std::vector<cv::Point3f> coords;
  std::vector<int> ids;
  std::vector<std::vector<Feature>> observations;
} LandmarkMapAsVectors;

std::vector<cv::Point3f> unpack_landmark_vector(
    std::vector<Landmark> landmarks);

LandmarkMapAsVectors unpack_landmark_map(
    landmark_map_t landmarks);

#endif
