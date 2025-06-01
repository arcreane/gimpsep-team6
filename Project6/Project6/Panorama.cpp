#include "panorama.h"
#include <opencv2/stitching.hpp>
#include <iostream>

namespace panorama {

    int run(int argc, char** argv) {
        if (argc < 4) {
            std::cerr << "Usage: panorama <img1> <img2> [...] <output.jpg>\n";
            return 1;
        }

        std::vector<cv::Mat> images;
        for (int i = 2; i < argc - 1; ++i) {
            cv::Mat img = cv::imread(argv[i]);
            if (img.empty()) {
                std::cerr << "Erreur de lecture : " << argv[i] << "\n";
                return 1;
            }
            images.push_back(img);
        }

        cv::Mat pano;
        auto stitcher = cv::Stitcher::create(cv::Stitcher::PANORAMA);
        auto status = stitcher->stitch(images, pano);

        if (status != cv::Stitcher::OK) {
            std::cerr << "Échec du panorama. Code : " << int(status) << "\n";
            return 1;
        }

        std::string output = argv[argc - 1];
        cv::imwrite(output, pano);
        std::cout << "Panorama enregistré : " << output << "\n";

        return 0;
    }

}
