#include "canny.hpp"
#include "../../img_io.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

namespace canny {
    int run(int argc, char** argv) {
        if (argc < 9) {
            std::cerr << "Usage: canny --th1 <t1> --th2 <t2> --kernel <k> in.jpg out.png" << std::endl;
            return 1;
        }
        int t1 = std::stoi(argv[3]);
        int t2 = std::stoi(argv[5]);
        int k = std::stoi(argv[7]);
        cv::Mat img = loadOrExit(argv[8]);
        cv::Mat gray, edges;
        cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
        cv::Canny(gray, edges, t1, t2, k);
        saveOrExit(argv[9], edges);
        return 0;
    }
} // namespace canny