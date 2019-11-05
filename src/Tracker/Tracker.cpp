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
 * No functions are implemented.  */ 
Tracker::Tracker() 
{
  params_ = TrackerParams();
}

Tracker::Tracker(TrackerParams params) 
{
  params_ = params;
}

feature_map_t Tracker::track_features(
    feature_map_t previous_features,
    const cv::Mat previous_image,
    const cv::Mat next_image)
{
  feature_map_t output;
  return output;
}

TrackerParams Tracker::get_params()
{
  return params_;
}
