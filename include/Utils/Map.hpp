#ifndef MAP_HPP_INCLUDE
#define MAP_HPP_INCLUDE

#include <vector>

#include <opencv2/core.hpp> 

#include "Utils/Landmark.hpp"
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

    // Getters
    landmark_map_t get_landmarks();
    frame_map_t get_frames();

    // Setters
    void set_landmarks(landmark_map_t landmarks);
    void set_frames(frame_map_t frames);

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
