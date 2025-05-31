#ifndef CANNY_FILTER_HPP
#define CANNY_FILTER_HPP

#include "AbstractFilter.hpp"

class CannyFilter : public AbstractFilter {
private:
    int threshold1, threshold2, apertureSize;

public:
    CannyFilter(int t1, int t2, int apertureSize);
    void apply(const cv::Mat& input, cv::Mat& output) override;
};

#endif
