#include "FeatureTracker.hpp"

FeatureTracker::FeatureTracker(Camera cam)
{
  cam_ = cam;
  id_counter_ = 0;
  frame_counter_ = 0;
  // TODO: mask_ = cv::Mat::zeros(cam_.width, cam_.height, CV_8UC1);
}

bool FeatureTracker::process_image(cv::Mat image)
{
  frame_counter_++;
  std::vector<cv::Point2f> temp_corners;
  new_pts.clear(); // This is where work is done before pushing to cur_pts

  // TODO: Add a flag/check for descriptors so can either 
  // use optical flow tracking or descriptor matching
  // TODO: Write a Detector class that FeatureTrackers own

  if (id_counter_ == 0) { // Haven't processed an image yet
    // Initialize features

    // 1. Detect features in the image
    cv::goodFeaturesToTrack(image, temp_corners, 500, 0.01, 10, cv::Mat(), 3, 3, 0, 0.04);
    std::vector<cv::Point2f> temp_norms = cam_.normalize_points(temp_corners);

    // 2. Create Feature for each and give id
    for (int i = 0; i < temp_corners.size(); i++)
    {
      Feature temp_feature = Feature(temp_corners[i], temp_norms[i]);
      temp_feature.id = ++id_counter_; // First feature has ID 1
      temp_feature.frame_id = frame_counter_; // 
      new_pts.push_back(temp_feature);
    }

    // Fill cur and prev 
    cur_pts = new_pts;
    prev_pts = new_pts;
    return true;

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

    return true;
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

