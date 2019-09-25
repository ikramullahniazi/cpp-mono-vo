#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp> // For undistortPoints()

class Camera {
  public:
    Camera(cv::Mat K, cv::Mat dist);
    std::vector<cv::Point2f> normalize_points(std::vector<cv::Point2f> pixel_coords);
  private:
    cv::Mat intrinsic_params_;
    cv::Mat distortiion_coeffs_;
};
