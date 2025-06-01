#ifndef BRIGHTNESS_FILTER_HPP
#define BRIGHTNESS_FILTER_HPP

#include "AbstractFilter.hpp"

class BrightnessFilter : public AbstractFilter {
private:
    int beta;

public:
    explicit BrightnessFilter(int beta);
    void apply(const cv::Mat& input, cv::Mat& output) override;
};

#endif