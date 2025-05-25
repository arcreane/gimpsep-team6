#include "grayscale.hpp"
#include "img_io.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

namespace grayscale {
    int run(int argc, char** argv) {
        if (argc != 4) {
            std::cerr << "Usage: mini-gimp grayscale <input_image_path> <output_image_path>" << std::endl;
            return 1;
        }

        std::string input_path = argv[2];
        std::string output_path = argv[3];

        cv::Mat input_image = loadOrExit(input_path);
        cv::Mat output_image;

        cv::cvtColor(input_image, output_image, cv::COLOR_BGR2GRAY);

        saveOrExit(output_path, output_image);
        return 0;
    }
} // namespace grayscale 