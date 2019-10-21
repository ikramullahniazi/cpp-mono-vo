#include "FeatureTracker.hpp"

FeatureTracker::FeatureTracker(std::shared_ptr<Camera> camera,
    std::shared_ptr<Detector> detector,
    std::shared_ptr<Tracker> tracker)
{
  camera_ = camera;
  detector_ = detector;
  tracker_ = tracker;
  frame_counter_ = 0;
}

FeatureTracker::FeatureTracker(Camera camera,
    Detector detector,
    Tracker tracker)
{
  camera_ = std::make_shared<Camera>(camera.get_intrinsic_params(),
      camera.get_distortion_coeffs(),
      camera.get_size());
  detector_ = std::make_shared<Detector>(detector.get_params());
  tracker_ = std::make_shared<Tracker>(tracker.get_params());
  frame_counter_ = 0;
}

bool FeatureTracker::process_image(const cv::Mat image)
{
  new_features_.clear(); // This is where work is done before pushing to cur_pts

  if (current_features_.size() == 0) { // Haven't processed an image yet
    // Initialize features
    new_features_ = detector_->detect_features(image);

    // TODO: populate frame_id field in points

    // Fill cur and prev 
    current_features_ = new_features_;
    previous_features_ = new_features_;

    current_image_ = image;
    previous_image_ = image;

    frame_counter_++;
    return true;

  } else {
    // Track features into new frame
    previous_image_ = current_image_;
    previous_features_ = current_features_;
    current_image_ = image;

    new_features_ = tracker_->track_features(
        previous_features_,
        previous_image_,
        current_image_);

    // New features contains features from previous image that have been
    // successfully matched in the incoming image

    // TODO: Detect more features to keep a minimum number
    // Steps:
    // 1. Create mask
    // 2. Detect features using mask
    // 3. Append to new_features

    current_features_ = new_features_;
    new_features_.clear();

    frame_counter_++;
    return true;
  }
  
  frame_counter_++;
  return false;
}

std::vector<Feature> FeatureTracker::get_data()
{
  return current_features_;
}

void FeatureTracker::set_camera(std::shared_ptr<Camera> camera)
{
  camera_ = camera;
}

void FeatureTracker::set_detector(std::shared_ptr<Detector> detector) 
{
  detector_ = detector;
}

void FeatureTracker::set_tracker(std::shared_ptr<Tracker> tracker)
{
  tracker_ = tracker;
}

cv::Mat FeatureTracker::generate_mask_from_features_(std::vector<Feature> features)
{
  cv::Mat mask = cv::Mat::ones(camera_->get_size(), CV_8UC1);

  for (Feature f : features) {
    // Mask out feature
    cv::Point2f coords = f.raw_coords;
    int col = coords.x;
    int row = coords.y;
    mask.at<uint8_t>(row, col) = 0;
  }

  return mask;
}
