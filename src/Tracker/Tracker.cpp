#include "Tracker/Tracker.hpp"

/*
 * This is the parent class for all TrackerParams.
 * No functions are implemented.
 */
TrackerParams::TrackerParams()
{
  config_();
}

void TrackerParams::config_()
{

}

/*
 * This is the parent class for all Trackers.
 * No functions are implemented.
 */

Tracker::Tracker() 
{
  params_ = TrackerParams();
}

Tracker::Tracker(TrackerParams params) 
{
  params_ = params;
}

std::vector<Feature> Tracker::track_features(
    const std::vector<Feature> previous_features,
    const cv::Mat previous_image,
    const cv::Mat next_image)
{
  std::vector<Feature> out_vec;
  return out_vec;
}
