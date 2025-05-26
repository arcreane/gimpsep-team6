#include "flip.hpp"
#include "img_io.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

namespace Rota {
    int run(int argc, char** argv) {
        if (argc < 5 || std::string(argv[2]) != "--angle") {
            std::cerr << "Usage: Rota --angle <value> in.jpg out.jpg" << std::endl;
            return 1;
        }
        int angle = std::stoi(argv[3]);
        cv::Mat img = loadOrExit(argv[4]);
        cv::Point2f center(src.cols / 2.0F, src.rows / 2.0F);
        cv::Mat out;
        cv::getRotationMatrix2D(center, angle, 1.0);
        cv::warpAffine(img, out, rotMat, img.size());
        saveOrExit(argv[5], out);
        return 0;
    }
} // namespace Rota
