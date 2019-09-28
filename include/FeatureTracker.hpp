#ifndef FEATURE_TRACKER_HPP_INCLUDE
#define FEATURE_TRACKER_HPP_INCLUDE

/*
 * This class tracks features from a previous frame into the current frame.
 * If needed, it also detects new features to maintain a minimum number.
 */

#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp> // for color map conversions, goodFeaturesToTrack
#include <opencv2/video.hpp> // for optical flow

#include "Camera.hpp"
#include "Feature.hpp"

class FeatureTracker {
  public:
    // Constructor
    FeatureTracker(Camera cam);

    // Create features from incoming image
    bool process_image(cv::Mat image);

    // Return features
    std::vector<Feature> get_data();

  private:
    // Current and previous points for tracking
    std::vector<Feature> prev_pts, cur_pts;
    
    Camera cam_;
};

#endif
