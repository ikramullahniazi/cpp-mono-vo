#include "Utils/Pose.hpp"

Pose::Pose()
{
  float t0[3] = {0, 0, 0};

  R = cv::Mat::eye(3, 3, CV_32F);
  t = cv::Mat(3, 1, CV_32F, t0);
}

Pose::Pose(cv::Mat rotation, cv::Mat translation)
{
  // TODO: Check valid input
  R = rotation;
  t = translation;
}

Pose Pose::inv()
{
  cv::Mat new_R, new_t;
  new_R = R.inv();
  new_t = -new_R * t;

  return Pose(new_R, new_t);
}
cv::Mat form_transformation_matrix(
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

  return T;
}


std::ostream& operator<< (std::ostream &out, Pose const& pose)
{
  // Print in the form of KITTI pose
  cv::Mat T = form_transformation_matrix(pose.R, pose.t);

  for (int i = 0; i < T.rows-1; ++i)
  {
    for (int j = 0; j < T.cols; ++j)
    {
      out << T.at<float>(i,j);
      if (i != 2 || j != 3)
      {
        out << " ";
      }
    }
  }

  return out;

}
