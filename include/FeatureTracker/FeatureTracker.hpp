#ifndef FEATURE_TRACKER_HPP_INCLUDE
#define FEATURE_TRACKER_HPP_INCLUDE

/*
 * This class tracks features from a previous frame into the current frame.
 * If needed, it also detects new features to maintain a minimum number.
 */

#include <vector>
#include <algorithm> // for copy()
#include <iterator> // for back_insertej

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp> // for color map conversions, goodFeaturesToTrack
#include <opencv2/video.hpp> // for optical flow

#include "Utils/Camera.hpp"
#include "Utils/Feature.hpp"

class FeatureTracker {
  public:
    // Constructor
    FeatureTracker(Camera cam);

    // Create features from incoming image
    bool process_image(cv::Mat image);

    // Return features
    bool get_data(std::vector<Feature> out_vec);

  private:
    // Current and previous points for tracking
    // cur_pts is the features from the most recent image
    // prev_pts is the features from the image before that one
    std::vector<Feature> prev_pts, cur_pts, new_pts;

    // counter for giving features IDs
    uint64_t id_counter_; 

    // counter for number of frames processed
    uint64_t frame_counter_;

    // Mask for ignoring regions of image
    cv::Mat mask_;

    // Self explanatory
    Camera cam_;

    // TODO
    // -> 
    // Detector det_;
};

#endif
