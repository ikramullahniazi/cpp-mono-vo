#include "FeatureTracker.hpp"

FeatureTracker::FeatureTracker(Camera camera)
{
  camera_ = camera;
  frame_counter_ = 0;
  // TODO: mask_ = cv::Mat::zeros(cam_.width, cam_.height, CV_8UC1);
}

bool FeatureTracker::process_image(const cv::Mat image)
{
  new_pts.clear(); // This is where work is done before pushing to cur_pts

  if (cur_pts.size() == 0) { // Haven't processed an image yet
    // Initialize features
    new_pts = detector_.detect_features(image);

    // TODO: populate frame_id field in points

    // Fill cur and prev 
    cur_pts = new_pts;
    prev_pts = new_pts;

    frame_counter_++;
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

    frame_counter_++;
    return true;
  }
  
  frame_counter_++;
  return false;
}

std::vector<Feature> FeatureTracker::get_data()
{
  return cur_pts;
}

