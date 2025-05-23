#include "brightness.hpp"
#include "../../img_io.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

namespace brightness {
    int run(int argc, char** argv) {
        if (argc < 5 || std::string(argv[2]) != "--beta") {
            std::cerr << "Usage: brightness --beta <value> in.jpg out.jpg" << std::endl;
            return 1;
        }
        int beta = std::stoi(argv[3]);
        cv::Mat img = loadOrExit(argv[4]);
        cv::Mat out;
        img.convertTo(out, -1, 1.0, beta);
        saveOrExit(argv[5], out);
        return 0;
    }
} // namespace brightness