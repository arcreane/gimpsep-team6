#pragma once
#include <opencv2/opencv.hpp>

cv::Mat loadOrExit(const std::string& path);
void saveOrExit(const std::string& path, const cv::Mat& img);
