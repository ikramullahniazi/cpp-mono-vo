#include "FeatureTracker.hpp"

FeatureTracker::FeatureTracker(Camera cam)
{
  cam_ = cam;
  id_counter_ = 0;
  // TODO: mask_ = cv::Mat::zeros(cam_.width, cam_.height, CV_8UC1);
}

bool FeatureTracker::process_image(cv::Mat image)
{
  // TODO: Add a flag/check for descriptors so can either 
  // use optical flow tracking or descriptor matching
  // TODO: Write a Detector class that FeatureTrackers own

  if (id_counter_ == 0) { // Haven't processed an image yet
    // Initialize features

    // 1. Detect features in the image

    // 2. Create Feature for each and give id

  } else {
    // Track features into new frame

    // 1. Build vector of points for optical flow tracking

    // 2. Track into new frame

    // 3. Remove outliers?

    // 4. Detect new features
    // TODO
    // cur_pts = det_.detect_features(image)

    // 5. If successful, cur -> prev, new -> cur
    // TODO Implement check 
    prev_pts = cur_pts;
    cur_pts = new_pts;
    new_pts.clear();

  }

  return false;
}

bool FeatureTracker::get_data(std::vector<Feature> out_vec)
{
  if (id_counter_ == 0) // No features yet
  { 
    return false;
  } 
  else 
  {
    out_vec = cur_pts;

    // TODO: Implement checks before returning true
    return true;
  }
}

