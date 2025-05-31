#include "GrayscaleFilter.hpp"
#include <opencv2/opencv.hpp>

void GrayscaleFilter::apply(const cv::Mat& input, cv::Mat& output) {
    cv::cvtColor(input, output, cv::COLOR_BGR2GRAY);
}
