#ifndef TRACKER_HPP_INCLUDE
#define TRACKER_HPP_INCLUDE

#include <vector>

#include <opencv2/core.hpp>

#include "Utils/Feature.hpp"

class TrackerParams {
  public:
    // Methods
    TrackerParams();
    void config_();
};

class Tracker {
  public:
    Tracker();
    Tracker(TrackerParams params);

    virtual std::vector<Feature> track_features(
        std::vector<Feature> previous_features,
        const cv::Mat previous_image,
        const cv::Mat new_image);

    TrackerParams get_params();
  private:
    // This contains the parameters to pass to the tracking/matching method.
    TrackerParams params_;
};

#endif
