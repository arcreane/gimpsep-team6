#ifndef BLUR_FILTER_HPP
#define BLUR_FILTER_HPP

#include "AbstractFilter.hpp"

class BlurFilter : public AbstractFilter {
private:
    int ksize;

public:
    explicit BlurFilter(int ksize);
    void apply(const cv::Mat& input, cv::Mat& output) override;
};

#endif