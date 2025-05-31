#ifndef FACE_BLUR_FILTER_HPP
#define FACE_BLUR_FILTER_HPP

#include "AbstractFilter.hpp"

class FaceBlurFilter : public AbstractFilter {
public:
    void apply(const cv::Mat& input, cv::Mat& output) override;
};

#endif
