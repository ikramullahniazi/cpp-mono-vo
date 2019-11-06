#ifndef FRAME_HPP_INCLUDE
#define FRAME_HPP_INCLUDE

#include <vector>
#include <opencv2/core.hpp>

#include "Utils/Feature.hpp"
#include "Utils/Pose.hpp"

/*
 * Modelled after ORB-SLAM keyframes, which store
 *  * T_iw which transform points from into the camera frame
 *  * Camera intrinsics
 *  * All features detected in the frame
 */

class Frame {
  public:
    // ------------
    // Constructors
    // ------------
    Frame();
    Frame(
        feature_map_t features,
        Pose pose,
        int frame_id,
        bool is_keyframe,
        bool is_processed);

    // ---------
    // Functions
    // ---------

    // ----
    // Data
    // ----

    // Feature observations in this image
    feature_map_t features;

    // Pose of the camera when this image was taken
    Pose pose;

    // Whether or not this is a keyframe
    bool is_keyframe;
    
    // Whether or not the estimator has processed the frame
    bool is_processed;

    // 
    int frame_id;

  private:
};

typedef std::map<int, Frame> frame_map_t;

#endif
