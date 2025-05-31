#include "CannyFilter.hpp"
#include <opencv2/imgproc.hpp>

CannyFilter::CannyFilter(int t1, int t2, int apertureSize)
    : threshold1(t1), threshold2(t2), apertureSize(apertureSize) {}

void CannyFilter::apply(const cv::Mat& input, cv::Mat& output) {
    cv::Mat gray;
    if (input.channels() == 3) {
        cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    }
    else {
        gray = input;
    }
    cv::Canny(gray, output, threshold1, threshold2, apertureSize);
}
