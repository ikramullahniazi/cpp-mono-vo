#include "FeatureTracker.hpp"
#include <iostream>

FeatureTracker::FeatureTracker(
    std::shared_ptr<Camera> camera,
    std::shared_ptr<Detector> detector,
    std::shared_ptr<Tracker> tracker)
{
  camera_ = camera;
  detector_ = detector;
  tracker_ = tracker;

  // Initialize other members
  frame_counter_ = 0;

  previous_features_ = std::vector<Feature>();
  current_features_ = std::vector<Feature>();
  new_features_ = std::vector<Feature>();

  previous_image_ = cv::Mat();
  current_image_ = cv::Mat();

  mask_ = cv::Mat();
}

Frame FeatureTracker::process_image(const cv::Mat image_bgr)
{
  cv::Mat image;
  cv::cvtColor(image_bgr, image, cv::COLOR_BGR2GRAY);

  if (frame_counter_ == 0) 
  {
    // Initialize features
    new_features_ = detector_->detect_features(image);

    // Using & to modify object rather than a copy
    for (Feature &feature : new_features_) {
      feature.frame_id = frame_counter_;
    }

    // Fill cur and prev 
    current_features_ = new_features_;
    previous_features_ = new_features_;

    current_image_ = image;
    previous_image_ = image;

    // Generate frame 0

    // Generate frame n
    Frame new_frame;
    new_frame.set_image(current_image_);
    new_frame.set_features(current_features_);
    new_frame.set_is_processed(false);
    new_frame.set_frame_id(frame_counter_++);

    return new_frame;

  } 
  else 
  {
    return Frame();
  }
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

cv::Mat FeatureTracker::generate_mask_from_features_(
    std::vector<Feature> features)
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
