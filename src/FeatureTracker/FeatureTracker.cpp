#include "FeatureTracker.hpp"
#include <iostream>

FeatureTrackerParams::FeatureTrackerParams()
{
  config_();
}

void FeatureTrackerParams::config_()
{
  minimum_features = 500;
}

FeatureTracker::FeatureTracker(
    std::shared_ptr<Camera> camera,
    std::shared_ptr<Detector> detector,
    std::shared_ptr<Tracker> tracker)
{
  camera_ = camera;
  detector_ = detector;
  tracker_ = tracker;
  params_ = FeatureTrackerParams();


  previous_features_ = feature_map_t();
  current_features_ = feature_map_t();
  new_features_ = feature_map_t();

  previous_image_ = cv::Mat();
  current_image_ = cv::Mat();

  mask_ = cv::Mat();

  frame_counter_ = 0;
}

FeatureTracker::FeatureTracker(
    std::shared_ptr<Camera> camera,
    std::shared_ptr<Detector> detector,
    std::shared_ptr<Tracker> tracker,
    FeatureTrackerParams params)
{
  camera_ = camera;
  detector_ = detector;
  tracker_ = tracker;
  params_ = params;


  previous_features_ = feature_map_t();
  current_features_ = feature_map_t();
  new_features_ = feature_map_t();

  previous_image_ = cv::Mat();
  current_image_ = cv::Mat();

  mask_ = cv::Mat();

  frame_counter_ = 0;
}

Frame FeatureTracker::process_image(cv::Mat image)
{
  /*
   * Important cases:
   * - frame_counter_ == 0 -> create first frame, do nothing after
   * - frame_counter_ > 0 -> track + detect more features
   */

  if (frame_counter_ == 0) 
  {
    // Initialize features
    new_features_ = detect_features_(image);

    // Fill cur and prev 
    current_features_ = new_features_;
    current_image_ = image;

    // Generate frame 0
    Frame first_frame = Frame();
    first_frame.features = current_features_;
    first_frame.is_processed = false;
    first_frame.frame_id = frame_counter_++;

    return first_frame;
  } 
  else 
  {
    // Track features into next frame
    // Process:
    // 1. Find previous features in current frame
    // 2. Detect new features if too few survive
    // 3. Create frame with all features
    new_features_ = track_features_(
        current_features_,
        current_image_,
        image);

    new_features_ = repopulate_features_(new_features_,image);

    previous_features_ = current_features_;
    previous_image_ = current_image_;

    current_features_ = new_features_;
    current_image_ = image;

    Frame next_frame = Frame();
    next_frame.features = current_features_;
    next_frame.is_processed = false;
    next_frame.frame_id = frame_counter_++;
    
    return next_frame;
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
    feature_map_t features)
{
  cv::Mat mask = cv::Mat::ones(camera_->size, CV_8UC1);

  for (auto const& f : features) {
    cv::Point2f coords = f.second.coords;
    int col = coords.x;
    int row = coords.y;
    mask.at<uint8_t>(row, col) = 0;
  }

  return mask;
}

feature_map_t FeatureTracker::track_features_(
    feature_map_t current_features,
    cv::Mat current_image,
    cv::Mat new_image)
{
  feature_map_t out_map = tracker_->track_features(
      current_features,
      current_image,
      new_image);

  for (auto &f : out_map) 
  {
    f.second.frame_id = frame_counter_;
  }

  return out_map;
}

feature_map_t FeatureTracker::detect_features_(
    cv::Mat new_image)
{
  feature_map_t out_map = detector_->detect_features(
      new_image);

  for (auto &f : out_map) {
    f.second.frame_id = frame_counter_;
  }

  return out_map;
}

feature_map_t FeatureTracker::repopulate_features_(
    feature_map_t existing_features,
    cv::Mat image)
{
  cv::Mat mask = generate_mask_from_features_(existing_features);
  int num_features_needed = params_.minimum_features - existing_features.size();

  if (num_features_needed < 0)
  {
    num_features_needed = 0;
  }
  
  feature_map_t new_features = detector_->detect_features(
      image,
      num_features_needed,
      mask);
  
  // Merge maps
  existing_features.insert(new_features.begin(), new_features.end());

  return existing_features;
}

