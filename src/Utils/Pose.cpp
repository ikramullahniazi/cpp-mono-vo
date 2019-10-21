#include "Utils/Pose.hpp"

Pose::Pose()
{
  float t0[3] = {0, 0, 0};
  float r0[3] = {0, 0, 0};
  set_rotation(r0);
  set_translation(t0);
}

Pose::Pose(cv::Mat rotation, cv::Mat translation)
{
  set_rotation(rotation);
  set_translation(translation);
}

void Pose::set_rotation(cv::Mat rotation)
{
  int rotation_rows = rotation.rows; // both options have 3 rows, check here
  int rotation_cols = rotation.cols;
  // matrices will have cols == 3, vectors will have cols == 1
  switch (rotation_cols)
  {
    case 1: // rotation is a vector
      rotation_ = rotation;
    case 3: // rotation is a matrix
      // TODO: Implement rodrigues' formula
    default: // wrong size
  }
}

void Pose::set_translation(cv::Mat translation)
{
  int translation_rows = translation.rows; // should be 3
  int translation_cols = rotation.cols; // should be 1

  translation_ = translation;
}

cv::Mat get_rotation_vector()
{
  return rotation_;
}

cv::Mat get_rotation_matrix()
{
  //TODO: implement rodrigues' formula
}

cv::Mat get_translation_vector()
{
  return translation_;
}
