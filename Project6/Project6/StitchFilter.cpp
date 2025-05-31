#include "StitchFilter.hpp"
#include "img_io.hpp"
#include <opencv2/stitching.hpp>
#include <iostream>

bool StitchFilter::stitchImages(const std::vector<std::string>& inputPaths, const std::string& outputPath) {
    std::vector<cv::Mat> imgs;
    for (const auto& path : inputPaths) {
        imgs.push_back(loadOrExit(path));
    }

    cv::Mat pano;
    auto stitcher = cv::Stitcher::create(cv::Stitcher::PANORAMA);
    auto status = stitcher->stitch(imgs, pano);

    if (status != cv::Stitcher::OK) {
        std::cerr << "Error stitching images" << std::endl;
        return false;
    }

    saveOrExit(outputPath, pano);
    return true;
}
