#ifndef FEATURE_TRACKER_HPP_INCLUDE
#define FEATURE_TRACKER_HPP_INCLUDE

/*
 * This class is part of the front end of a visual odometry system.
 * It takes in images and extracts measurements in the form of
 * features tracked from image to image.
 * If needed, it also detects new features to maintain a minimum
 * number.
 */

#include <vector>
#include <algorithm> // for copy()
#include <iterator> // for back_insert

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp> // for color map conversions, goodFeaturesToTrack

#include "Utils/Camera.hpp"
#include "Utils/Feature.hpp"
#include "Utils/Frame.hpp"

// Including superclass -> use any detector
#include "Detector/Detector.hpp"

// Including superclass -> use any tracker
#include "Tracker/Tracker.hpp"

class FeatureTrackerParams {
  public:
    // ------------
    // Constructors
    // ------------
    FeatureTrackerParams();

    // ---------
    // Functions
    // ---------

    // ----
    // Data
    // ----
    int minimum_features;

  private:
    // -------------
    // Owned Objects
    // -------------

    // ---------
    // Functions
    // ---------
    void config_();

    // ----
    // Data
    // ----

};

class FeatureTracker {
  public:
    // Constructor
    FeatureTracker(
        std::shared_ptr<Camera> camera,
        std::shared_ptr<Detector> detector,
        std::shared_ptr<Tracker> tracker);

    FeatureTracker(
        std::shared_ptr<Camera> camera,
        std::shared_ptr<Detector> detector,
        std::shared_ptr<Tracker> tracker,
        FeatureTrackerParams params);

    // Create features from incoming image
    Frame process_image(cv::Mat image);

    // Setters
    void set_camera(std::shared_ptr<Camera> camera);
    void set_detector(std::shared_ptr<Detector> detector);
    void set_tracker(std::shared_ptr<Tracker> tracker);

  private:
    // Owned objects
    std::shared_ptr<Camera> camera_;
    std::shared_ptr<Detector> detector_;
    std::shared_ptr<Tracker> tracker_;
    FeatureTrackerParams params_;

    // Functions
    cv::Mat generate_mask_from_features_(
        std::vector<Feature> features);

    // Utility wrappers to access tracker and detector
    std::vector<Feature> track_features_(
        std::vector<Feature> current_features,
        cv::Mat current_image,
        cv::Mat new_image);
    std::vector<Feature> detect_features_(cv::Mat new_image);
    std::vector<Feature> repopulate_features_(
        std::vector<Feature> existing_features,
        cv::Mat image);

    // Data

    // Current and previous points for tracking
    // cur_pts is the features from the most recent image
    // prev_pts is the features from the image before that one
    // new_pts is a workspace for processing detections before adding to system
    std::vector<Feature> previous_features_;
    std::vector<Feature> current_features_;
    std::vector<Feature> new_features_;
    
    // Current and previous images for tracking
    cv::Mat previous_image_;
    cv::Mat current_image_;

    // Mask for ignoring regions of image
    cv::Mat mask_;

    // counter for number of frames processed
    int frame_counter_;

};

#endif
