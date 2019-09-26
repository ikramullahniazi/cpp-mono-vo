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

class FeatureTracker {
  public:
    FeatureTracker();
    bool process_image(cv::Mat image);
  private:
    // Pixel values of tracked points
    std::vector<cv::Point2f> prev_pts_, cur_pts_;
    // Undistorted/normalized coordinates of tracked points
    std::vector<cv::Point2f> prev_pts_undist_, cur_pts_undist_;
    
    Camera cam_;
};

#endif
