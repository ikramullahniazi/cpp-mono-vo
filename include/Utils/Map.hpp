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

    // ---------
    // Functions
    // ---------
    bool insert_frame(Frame frame);
    bool insert_landmark(Landmark landmark);

    // Getters
    std::vector<Landmark> get_landmarks();
    std::vector<Frame> get_keyframes();

    // Setters
    void set_landmarks(std::vector<Landmark> landmarks);
    void set_keyframes(std::vector<Frame> keyframes);

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
    std::vector<Landmark> landmarks_;
    std::vector<Frame> keyframes_;

};

#endif
