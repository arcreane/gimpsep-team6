#include "BrightnessFilter.hpp"
#include <opencv2/opencv.hpp>

BrightnessFilter::BrightnessFilter(int beta) : beta(beta) {}

void BrightnessFilter::apply(const cv::Mat& input, cv::Mat& output) {
    input.convertTo(output, -1, 1.0, beta);
}
