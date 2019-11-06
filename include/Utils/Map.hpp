#ifndef MAP_HPP_INCLUDE
#define MAP_HPP_INCLUDE

#include <vector>

#include <opencv2/core.hpp> 

#include "Utils/Landmark.hpp"
#include "Utils/Feature.hpp"
#include "Utils/Frame.hpp"

class Map {
  public:
    // ------------
    // Constructors
    // ------------
    Map();
    Map(
        landmark_map_t landmarks,
        frame_map_t frames);

    // ---------
    // Functions
    // ---------
    bool insert_frame(Frame frame);
    bool insert_landmark(Landmark landmark);

    landmark_map_t get_landmarks();
    bool contains_landmark(int id);
    Landmark get_landmark(int id);

    frame_map_t get_frames();
    bool contains_frame(int id);
    Frame get_frame(int id);

    void set_landmarks(landmark_map_t landmarks);
    void set_frames(frame_map_t frames);

    std::pair<feature_map_t, landmark_map_t> filter_by_features(
        feature_map_t features);

    // ----
    // Data
    // ----

  private:
    // -------------
    // Owned Objects
    // -------------
    
    // ---------
    // Functions
    // ---------
    
    // ----
    // Data
    // ----
    landmark_map_t landmarks_;
    frame_map_t frames_;

};

#endif
