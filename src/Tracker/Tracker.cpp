#include "Tracker/Tracker.hpp"

/*
 * This is the default (reference) implementation of a feature tracker.
 * It uses sparse optical flow to track features into the next frame.
 */

Tracker::Tracker() {

}

Tracker::Tracker(TrackerParams params) {

}

std::vector<Feature> Tracker::track_features(
    const std::vector<Feature> previous_features,
    const cv::Mat previous_image,
    const cv::Mat next_image)
  {

}

