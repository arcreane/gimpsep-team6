#include "stitch.hpp"
#include "img_io.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp>
#include <iostream>

namespace stitch {
    int run(int argc, char** argv) {
        if (argc < 5) {
            std::cerr << "Usage: stitch img1 img2 [img3 …] out.jpg" << std::endl;
            return 1;
        }
        std::vector<cv::Mat> imgs;
        for (int i = 2; i < argc - 1; ++i)
        {
            imgs.push_back(loadOrExit(argv[i]));
        }
        cv::Mat pano;
        cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;
        auto stitcher = cv::Stitcher::create(mode);
        cv::Stitcher::Status status = stitcher->stitch(imgs, pano);
        if (status != cv::Stitcher::OK) {
            std::cerr << "Error stitching images" << std::endl;
            return 1;
        }
        saveOrExit(argv[argc - 1], pano);
        return 0;
    }
} // namespace stitch