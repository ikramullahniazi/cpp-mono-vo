#include "Tracker/TrackerParams.hpp"

// Create a params object with defaults for given detector.
// Parameters are changed after creation.

TrackerParams::TrackerParams()
{
  config_();
}

void TrackerParams::config_()
{
  win_size_ = cv::Size(21,21);
  term_criteria_ = 
    cv::TermCriteria(cv::TermCriteria::COUNT|cv::TermCriteria::EPS,
        30,
        0.01);
  flags_ = cv::OPTFLOW_LK_GET_MIN_EIGENVALS ;
  min_eig_threshold_ = 0.0001;
}
