#include "resize.hpp"
#include "../../img_io.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

namespace resize {
    int run(int argc, char** argv) {
        if (argc < 7) {
            std::cerr << "Usage: resize (--fx <f> --fy <f> | --width <w> --height <h>) in.jpg out.jpg" << std::endl;
            return 1;
        }
        cv::Mat img = loadOrExit(argv[(std::string(argv[2]) == "--fx") ? 4 : 6]);
        cv::Mat out;
        if (std::string(argv[2]) == "--fx" && std::string(argv[4]) == "--fy") {
            double fx = std::stod(argv[3]);
            double fy = std::stod(argv[5]);
            cv::resize(img, out, cv::Size(), fx, fy);
        }
        else if (std::string(argv[2]) == "--width" && std::string(argv[4]) == "--height") {
            int w = std::stoi(argv[3]);
            int h = std::stoi(argv[5]);
            cv::resize(img, out, cv::Size(w, h));
        }
        else {
            std::cerr << "Invalid options" << std::endl;
            return 1;
        }
        saveOrExit(argv[6], out);
        return 0;
    }
} // namespace resize