#ifndef GRAYSCALE_FILTER_HPP
#define GRAYSCALE_FILTER_HPP

#include "AbstractFilter.hpp"

class GrayscaleFilter : public AbstractFilter {
public:
    void apply(const cv::Mat& input, cv::Mat& output) override;
};

#endif  