#include "Estimator.hpp"

/*
 * EstimatorParams implementations
 */

// Public

// ------------
// Constructors
// ------------
EstimatorParams::EstimatorParams()
{
  config_();
}

// ---------
// Functions
// ---------

void EstimatorParams::config_()
{
  manual_initialization = false;
}

// Private

// ---------
// Functions
// ---------

/*
 * Estimator implementations
 */

// Public

// ------------
// Constructors
// ------------
Estimator::Estimator()
{
  initialize_position_();
}

Estimator::Estimator(std::shared_ptr<Camera> camera,
    std::shared_ptr<Map> map)
{
  camera_ = camera;
  map_ = map;

  initialize_position_();
}

Estimator::Estimator(Camera camera, Map map)
{
  camera_ = std::make_shared<Camera>(camera.get_intrinsic_params(),
      camera.get_distortion_coeffs(),
      camera.get_size());
  map_ = std::make_shared<Map>();

  initialize_position_();
}

// ---------
// Functions
// ---------

void Estimator::initialize_position_()
{
  float t0[3] = {0, 0, 0};
  float r0[3] = {0, 0, 0};

  cv::Mat rotation_vector = cv::Mat(3, 1, CV_32F, r0);
  cv::Mat translation_vector = cv::Mat(3, 1, CV_32F, t0);

  initialize_position_(rotation_vector, translation_vector);
}

void Estimator::initialize_position_(cv::Mat r0,
    cv::Mat t0)
{
  pose_ = Pose(r0, t0);
}

void Estimator::initialize_position_(Pose pose0)
{
  pose_ = pose0;
}

// Private

// ---------
// Functions
// ---------

bool Estimator::manual_initialization_(
    Frame keyframe_1,
    Frame keyframe_2)
{
  /*
   * Process:
   * 1. Match features between frames
   * 2. Triangulate features
   * 3. Outlier rejection
   * 4. Populate map
   */

  return false;
}

