#include "Estimator.hpp"

Estimator::Estimator()
{
  float t0[3] = {0, 0, 0};
  tvec_ = cv::Mat(3,1,CV_32F, t0);
  float r0[3] = {0,0,0};
  rvec_ = cv::Mat(3,1,CV_32F, r0);
}


Estimator::Estimator(Camera cam)
{
  float t0[3] = {0, 0, 0};
  tvec_ = cv::Mat(3,1,CV_32F, t0);
  float r0[3] = {0,0,0};
  rvec_ = cv::Mat(3,1,CV_32F, r0);

  cam_ = cam;
}
