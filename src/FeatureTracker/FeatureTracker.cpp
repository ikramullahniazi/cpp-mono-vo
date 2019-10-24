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

Frame FeatureTracker::process_image(const cv::Mat image)
{
  new_features_.clear();

  if (frame_counter_ == 0) {
    // Initialize features
    new_features_ = detector_->detect_features(image);

    // Using & to modify object rather than a copy
    for (Feature &feature : new_features_) {
      feature.frame_id = frame_counter_;
    }

    // TODO: populate frame_id field in points

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

  } else {
    // Track features into new frame
    previous_image_ = current_image_;
    previous_features_ = current_features_;
    current_image_ = image;

    new_features_ = tracker_->track_features(
        previous_features_,
        previous_image_,
        current_image_);

    for (Feature &feature : new_features_)
    {
      feature.frame_id = frame_counter_;
    }

    // Detect more features to keep a minimum number
    //
    // 1. Create mask
    cv::Mat mask = generate_mask_from_features_(
        new_features_);
    // 2. Detect features using mask
    std::vector<Feature> additional_features = 
      detector_->detect_features(
          current_image_,
          mask);
    // 3. Append to new_features
    for (Feature &feature : additional_features)
    {
      feature.frame_id = frame_counter_;
      new_features_.push_back(feature);
    }

    current_features_ = new_features_;
    new_features_.clear();

    // Generate frame n
    Frame new_frame;
    new_frame.set_image(current_image_);
    new_frame.set_features(current_features_);
    new_frame.set_is_processed(false);
    new_frame.set_frame_id(frame_counter_++);

    return new_frame;
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
