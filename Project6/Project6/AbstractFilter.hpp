#ifndef ABSTRACT_FILTER_HPP
#define ABSTRACT_FILTER_HPP

#include <opencv2/opencv.hpp>
#include <string>

class AbstractFilter {
public:
    virtual void apply(const cv::Mat& input, cv::Mat& output) = 0;
    virtual ~AbstractFilter() {}
};

#endif