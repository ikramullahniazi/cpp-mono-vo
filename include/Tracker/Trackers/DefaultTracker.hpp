#ifndef DEFAULT_TRACKER_HPP_INCLUDE
#define DEFAULT_TRACKER_HPP_INCLUDE

#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/video.hpp>

#include "Utils/Feature.hpp"
#include "Tracker/Tracker.hpp"

class DefaultTrackerParams: public TrackerParams {
  public:
    // Methods
    DefaultTrackerParams();
    void config_();

    // Data
    cv::Size win_size;
    int max_level;
    cv::TermCriteria term_criteria;
    int flags;
    double min_eig_threshold;
};

class DefaultTracker: public Tracker {
  public:
    DefaultTracker();
    DefaultTracker(DefaultTrackerParams params);

    feature_map_t track_features(
        feature_map_t previous_features,
        const cv::Mat previous_image,
        const cv::Mat new_image);

  private:
    // This contains the parameters to pass to the tracking/matching method.
    DefaultTrackerParams params_;

    bool is_in_frame_(cv::Point2f point, cv::Mat image);
};

#endif
