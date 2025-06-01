#ifndef FACE_DETECT_FILTER_HPP
#define FACE_DETECT_FILTER_HPP

#include "AbstractFilter.hpp"
#include <vector>
#include <opencv2/opencv.hpp>

class FaceDetectFilter : public AbstractFilter {
public:
    void apply(const cv::Mat& input, cv::Mat& output) override;

    // We leave this for reuse in face blur
    std::vector<cv::Rect> detectFaces(const cv::Mat& input);
};

#endif // FACE_DETECT_FILTER_HPP
