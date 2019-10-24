#ifndef FRAME_HPP_INCLUDE
#define FRAME_HPP_INCLUDE

#include <vector>
#include <opencv2/core.hpp>

#include "Utils/Feature.hpp"
#include "Utils/Pose.hpp"

/*
 * 
 */

class Frame {
  public:
    // ------------
    // Constructors
    // ------------
    Frame();
    Frame(cv::Mat image,
        std::vector<Feature> features,
        Pose pose,
        uint64_t frame_id,
        bool is_keyframe,
        bool is_processed);

    // ---------
    // Functions
    // ---------
    // Getters
    bool get_is_keyframe();
    bool get_is_processed();
    cv::Mat get_image();
    std::vector<Feature> get_features();
    Pose get_pose();

    // Setters
    void set_is_keyframe(bool is_keyframe);
    void set_is_processed(bool is_processed);
    void set_image(cv::Mat image);
    void set_features(std::vector<Feature> features);
    void set_pose(Pose pose);
    void set_frame_id(uint64_t id);

    // ----
    // Data
    // ----

  private:
    // -------------
    // Owned Objects
    // -------------

    // ---------
    // Functions
    // ---------

    // ----
    // Data
    // ----
    cv::Mat image_;

    // Feature observations in this image
    std::vector<Feature> features_;

    // Pose of the camera when this image was taken
    Pose pose_;

    // Whether or not this is a keyframe
    bool is_keyframe_;
    
    // Whether or not the estimator has processed the frame
    bool is_processed_;

    // 
    uint64_t frame_id_;
};

#endif
