#include "MorphologyFilter.hpp"
#include <opencv2/imgproc.hpp>

MorphologyFilter::MorphologyFilter(int size, bool dilateFlag)
    : size(size), dilateFlag(dilateFlag) {}

void MorphologyFilter::apply(const cv::Mat& input, cv::Mat& output) {
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * size + 1, 2 * size + 1));
    if (dilateFlag)
        cv::dilate(input, output, kernel);
    else
        cv::erode(input, output, kernel);
}
