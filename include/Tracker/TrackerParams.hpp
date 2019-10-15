#ifndef TRACKER_PARAMS_HPP_INCLUDE
#define TRACKER_PARAMS_HPP_INCLUDE

#include <opencv2/core.hpp>
#include <opencv2/video/tracking.hpp>

class TrackerParams {
  public:
    // Methods
    TrackerParams();
    void config_();

    // Data
    cv::Size win_size_;
    int max_level_;
    cv::TermCriteria term_criteria_;
    int flags_;
    double min_eig_threshold_;
};

#endif

