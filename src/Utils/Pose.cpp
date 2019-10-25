#include "Utils/Pose.hpp"

Pose::Pose()
{
  float t0[3] = {0, 0, 0};
  float r0[3] = {0, 0, 0};

  cv::Mat rotation_vector = cv::Mat(3, 1, CV_32F, r0);
  cv::Mat translation_vector = cv::Mat(3, 1, CV_32F, t0);
  set_pose(rotation_vector, translation_vector);
}

Pose::Pose(cv::Mat rotation, cv::Mat translation)
{
  set_pose(rotation, translation);
}

bool Pose::set_rotation_(cv::Mat rotation)
{
  int cols = rotation.cols;
  bool rotation_success;
  cv::Mat rotation_vector, rotation_matrix;
  switch (cols)
  {
    case 1: // rotation is a vector
      rotation_vector = rotation;
      cv::Rodrigues(rotation, rotation_matrix);
      rotation_success = (set_rotation_vector_(rotation_vector) &&
          set_rotation_matrix_(rotation_matrix));
    case 3: // rotation is a matrix
      rotation_matrix = rotation;
      cv::Rodrigues(rotation, rotation_vector);
      rotation_success = (set_rotation_vector_(rotation_vector) &&
          set_rotation_matrix_(rotation_matrix));
    default: // not a valid format
      rotation_success = false;
  }
  return rotation_success;
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
  int rows = translation_vector.rows;
  int cols = translation_vector.cols;
  if (cols == 1 && rows == 3)
  {
    translation_vector_ = translation_vector;
    return true;
  } 
  else 
  {
    return false;
  }
}

bool Pose::set_transformation_matrix_(
    cv::Mat rotation_matrix,
    cv::Mat translation_vector)
{
  cv::Rect R_src_rect = cv::Rect(cv::Point(0,0), cv::Point(3,3));
  cv::Rect t_src_rect = cv::Rect(cv::Point(0,0), cv::Point(1,3));
  cv::Rect R_dst_rect = cv::Rect(cv::Point(0,0), cv::Point(3,3));
  cv::Rect t_dst_rect = cv::Rect(cv::Point(3,0), cv::Point(4,3));

  cv::Mat T = cv::Mat::eye(4, 4, CV_32F);
  rotation_matrix(R_src_rect).copyTo(
      T(R_dst_rect));
  translation_vector(t_src_rect).copyTo(
      T(t_dst_rect));

  transformation_matrix_ = T;
  return true; // TODO: More checking
}

bool Pose::set_pose(
    cv::Mat rotation,
    cv::Mat translation)
{
  bool rotation_success, translation_success, transformation_success;
  // Note: accept either rotation vector or rotation matrix
  rotation_success = set_rotation_(rotation);

  translation_success = set_translation_vector_(translation);

  transformation_success = set_transformation_matrix_(
      rotation_matrix_,
      translation_vector_);

  return (rotation_success && translation_success && transformation_success);
}

cv::Mat Pose::get_rotation_vector()
{
  return rotation_vector_;
}

cv::Mat Pose::get_rotation_matrix()
{
  return rotation_matrix_;
}

cv::Mat Pose::get_translation_vector()
{
  return translation_vector_;
}

cv::Mat Pose::get_transformation_matrix()
{
  return transformation_matrix_;
}
