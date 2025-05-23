#include "img_io.hpp"
#include <iostream>

cv::Mat loadOrExit(const std::string& p) {
    cv::Mat m = cv::imread(p);
    if (m.empty()) {
        std::cerr << "Error: cannot load " << p << std::endl;
        std::exit(1);
    }
    return m;
}

void saveOrExit(const std::string& p, const cv::Mat& m) {
    if (!cv::imwrite(p, m)) {
        std::cerr << "Error: cannot save " << p << std::endl;
        std::exit(1);
    }
}