#ifndef RESIZE_FILTER_HPP
#define RESIZE_FILTER_HPP

#include "AbstractFilter.hpp"

class ResizeFilter : public AbstractFilter {
private:
    double fx, fy;
    int width, height;
    bool useFactor;

public:
    ResizeFilter(double fx, double fy);      
    ResizeFilter(int width, int height);       
    void apply(const cv::Mat& input, cv::Mat& output) override;
};

#endif
