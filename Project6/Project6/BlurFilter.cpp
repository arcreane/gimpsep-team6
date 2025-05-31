#include "BlurFilter.hpp"
#include <opencv2/imgproc.hpp>

BlurFilter::BlurFilter(int ksize) : ksize(ksize) {}

void BlurFilter::apply(const cv::Mat& input, cv::Mat& output) {
    cv::GaussianBlur(input, output, cv::Size(ksize, ksize), 0);
}
