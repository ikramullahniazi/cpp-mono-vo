#include "Utils/Pose.hpp"

Pose::Pose()
{
  float t0[3] = {0, 0, 0};
  float r0[3] = {0, 0, 0};

  rotation_vector = cv::Mat(3, 1, CV_32F, r0);
  translation_vector = cv::Mat(3, 1, CV_32F, t0);
  set_rotation(rotation_vector);
  set_translation(translation_vector);
}

Pose::Pose(cv::Mat rotation, cv::Mat translation)
{
  set_rotation(rotation);
  set_translation(translation);
}

bool Pose::set_rotation(cv::Mat rotation)
{
  int rotation_rows = rotation.rows; // both options have 3 rows, check here
  if (rotation_rows != 3) 
  {
    return false;
  }

  int rotation_cols = rotation.cols;
  // matrices will have cols == 3, vectors will have cols == 1
  switch (rotation_cols)
  {
    case 1: // rotation is a vector
      rotation_ = rotation;
      return true;
    case 3: // rotation is a matrix
      // TODO: Implement rodrigues' formula
      return true;
    default: // wrong size
      return false;
  }
}

bool Pose::set_rotation_vector_(cv::Mat rotation_vector)
{
  int rows = rotation_vector.rows;
  int cols = rotation_vector.cols;

  if (rows == 3 && cols == 1)
  {
    rotation_vector_ = rotation_vector;
    return true;
  }
  else
  {
    return false;
  }
}

bool Pose::set_rotation_matrix_(cv::Mat rotation_matrix)
{
  int rows = rotation_matrix.rows;
  int cols = rotation_matrix.cols;

  if (rows == 3 && cols == 3)
  {
    rotation_matrix_ = rotation_matrix;
    return true;
  }
  else
  {
    return false;
  }
}


bool Pose::set_translation_vector_(cv::Mat translation_vector)
{
  if (translation_vector.width == 1 && translation_vector.height == 3)
  {
    translation_vector_ = translation_vector;
    return true;
  } 
  else 
  {
    return false;
  }
}

bool Pose::set_pose(cv::Mat rotation,
    cv::Mat translation)
{
  bool rotation_success, translation_success, transformation_success;
  // Note: accept either rotation vector or rotation matrix
  int cols = rotation.cols;
  cv::Mat rotation_vector, rotation_matrix;
  switch (cols)
  {
    case 1: // rotation is a vector
      rotation_vector = rotation;
      cv::Rodrigues(rotation, rotation_matrix);
      rotation_success = (set_rotation_vector(rotation_vector) &&
          set_rotation_matrix(rotation_matrix));
    case 3: // rotation is a matrix
      rotation_matrix = rotation;
      cv::Rodrigues(rotation, rotation_vector);
      rotation_success = (set_rotation_vector(rotation_vector) &&
          set_rotation_matrix(rotation_matrix));
    default: // not a valid format
      rotation_success = false;
  }

  translation_success = set_translation_vector_(translation);

  transformation_success = set_transformation_vector_(
      rotation_matrix_,
      translation_vector_);

  return (rotation_success && translation_success && transformation_success);
}

cv::Mat get_rotation_vector()
{
  return rotation_vector_;
}

cv::Mat get_rotation_matrix()
{
  return rotation_matrix_;
}

cv::Mat get_translation_vector()
{
  return translation_vector_;
}

cv::Mat get_transformation_matrix()
{
  return transformation_matrix_;
}
