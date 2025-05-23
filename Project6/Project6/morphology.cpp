#include "morphology.hpp"
#include "../../img_io.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

namespace morphology {
    int run(int argc, char** argv, bool dilateFlag) {
        if (argc < 5 || std::string(argv[2]) != "--size") {
            std::cerr << "Usage: " << (dilateFlag ? "dilate" : "erode")
                << " --size <n> in.jpg out.jpg" << std::endl;
            return 1;
        }
        int k = std::stoi(argv[3]);
        cv::Mat img = loadOrExit(argv[4]);
        cv::Mat out;
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * k + 1, 2 * k + 1));
        if (dilateFlag)
            cv::dilate(img, out, kernel);
        else
            cv::erode(img, out, kernel);
        saveOrExit(argv[5], out);
        return 0;
    }
} // namespace morphology