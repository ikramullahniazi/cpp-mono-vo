#ifndef FEATURE_TRACKER_HPP_INCLUDE
#define FEATURE_TRACKER_HPP_INCLUDE

/*
 * This class tracks features from a previous frame into the current frame.
 * If needed, it also detects new features to maintain a minimum number.
 */

#include <vector>
#include <algorithm> // for copy()
#include <iterator> // for back_insert

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp> // for color map conversions, goodFeaturesToTrack
#include <opencv2/video.hpp> // for optical flow

#include "Utils/Camera.hpp"
#include "Utils/Feature.hpp"

// Including superclass -> use any detector
#include "Detector/Detector.hpp"

// Including superclass -> use any tracker
#include "Tracker/Tracker.hpp"

class FeatureTracker {
  public:
    // Constructor
    FeatureTracker(Camera camera,
        Detector detector,
        Tracker tracker);

    // Create features from incoming image
    bool process_image(const cv::Mat image);

    // Return features
    std::vector<Feature> get_data();

    // Setters
    void set_camera(Camera camera);
    void set_detector(Detector detector);
    void set_tracker(Tracker tracker);

  private:
    // Owned objects
    std::shared_ptr<Camera> camera_;
    Detector detector_;
    Tracker tracker_;

    // Functions

    cv::Mat generate_mask_from_features_(std::vector<Feature> features);

    // Data

    // Current and previous points for tracking
    // cur_pts is the features from the most recent image
    // prev_pts is the features from the image before that one
    // new_pts is a workspace for processing detections before adding to system
    std::vector<Feature> previous_features_, current_features_, new_features_;
    
    // Current and previous images for tracking
    cv::Mat previous_image_, current_image_;

    // counter for number of frames processed
    uint64_t frame_counter_;

    // Mask for ignoring regions of image
    cv::Mat mask_;
};

#endif
