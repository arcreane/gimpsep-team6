#include "blur.hpp"
#include "img_io.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <stdexcept>

namespace blur {
    int run(int argc, char** argv) {
        if (argc != 6 || std::string(argv[2]) != "--ksize") {
            std::cerr << "Usage: mini-gimp blur --ksize <kernel_size> <input_image_path> <output_image_path>" << std::endl;
            return 1;
        }

        int ksize;
        try {
            ksize = std::stoi(argv[3]);
        } catch (const std::invalid_argument& ia) {
            std::cerr << "Error: kernel_size must be an integer." << std::endl;
            return 1;
        } catch (const std::out_of_range& oor) {
            std::cerr << "Error: kernel_size is out of range." << std::endl;
            return 1;
        }

        if (ksize <= 0 || ksize % 2 == 0) {
            std::cerr << "Error: kernel_size must be a positive odd integer." << std::endl;
            return 1;
        }

        std::string input_path = argv[4];
        std::string output_path = argv[5];

        cv::Mat input_image = loadOrExit(input_path);
        cv::Mat output_image;

        cv::GaussianBlur(input_image, output_image, cv::Size(ksize, ksize), 0);

        saveOrExit(output_path, output_image);
        return 0;
    }
} // namespace blur 