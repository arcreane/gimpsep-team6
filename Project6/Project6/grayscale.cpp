#include "GrayscaleFilter.hpp"
#include <opencv2/imgproc.hpp>

void GrayscaleFilter::apply(const cv::Mat& input, cv::Mat& output) {
    cv::cvtColor(input, output, cv::COLOR_BGR2GRAY);
}
