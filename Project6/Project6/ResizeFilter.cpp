#include "ResizeFilter.hpp"
#include <opencv2/imgproc.hpp>

ResizeFilter::ResizeFilter(double fx, double fy)
    : fx(fx), fy(fy), useFactor(true) {}

ResizeFilter::ResizeFilter(int width, int height)
    : width(width), height(height), useFactor(false) {}

void ResizeFilter::apply(const cv::Mat& input, cv::Mat& output) {
    if (useFactor)
        cv::resize(input, output, cv::Size(), fx, fy);
    else
        cv::resize(input, output, cv::Size(width, height));
}
