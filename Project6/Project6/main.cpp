#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>

#include "img_io.hpp"
#include "FilterRunner.hpp"
#include "BlurFilter.hpp"
#include "BrightnessFilter.hpp"
#include "MorphologyFilter.hpp"
#include "ResizeFilter.hpp"
#include "CannyFilter.hpp"
#include "GrayscaleFilter.hpp"
#include "FaceDetectFilter.hpp"
#include "FaceBlurFilter.hpp"
#include "StitchFilter.hpp"
#include "BgSubtract.hpp"
#include "VideoBrightnessProcessor.hpp"

void print_usage() {
    std::cerr << "Usage: mini-gimp <command> [options] <input> [<input2> …] <output>\n\n"
        << "Commands:\n"
        << "  grayscale in.jpg out.jpg\n"
        << "  blur --ksize <value> in.jpg out.jpg\n"
        << "  brightness --beta <value> in.jpg out.jpg\n"
        << "  dilate --size <value> in.jpg out.jpg\n"
        << "  erode --size <value> in.jpg out.jpg\n"
        << "  resize --fx <f> --fy <f> in.jpg out.jpg\n"
        << "  resize --width <w> --height <h> in.jpg out.jpg\n"
        << "  canny --th1 <t1> --th2 <t2> --kernel <k> in.jpg out.jpg\n"
        << "  stitch <img1> <img2> [img3 …] out.jpg\n"
        << "  bgsubtract [options] in.mp4 out.avi\n"
        << "  video --beta <value> in.mp4 out.mp4\n"
        << "  face_detect in.jpg out.jpg\n"
        << "  face_blur in.jpg out.jpg\n";
}

int main(int argc, char** argv) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    std::string cmd = argv[1];
    std::string manual = "manual.txt";
    if (cmd == "-h" || cmd == "--help") {
        std::ifstream manual("manual.txt");
        if (manual.is_open()) {
            std::cout << manual.rdbuf();
            return 0;
        }
        else {
            std::cerr << "manual.txt not found.\n";
            return 1;
        }
    }


    if (cmd == "grayscale") {
        if (argc != 4) return (print_usage(), 1);
        return FilterRunner::run(argv[2], argv[3], std::make_unique<GrayscaleFilter>());
    }
    else if (cmd == "blur") {
        if (argc != 6 || std::string(argv[2]) != "--ksize") return (print_usage(), 1);
        return FilterRunner::run(argv[4], argv[5], std::make_unique<BlurFilter>(std::stoi(argv[3])));
    }
    else if (cmd == "brightness") {
        if (argc != 6 || std::string(argv[2]) != "--beta") return (print_usage(), 1);
        return FilterRunner::run(argv[4], argv[5], std::make_unique<BrightnessFilter>(std::stoi(argv[3])));
    }
    else if (cmd == "dilate" || cmd == "erode") {
        if (argc != 6 || std::string(argv[2]) != "--size") return (print_usage(), 1);
        return FilterRunner::run(argv[4], argv[5], std::make_unique<MorphologyFilter>(std::stoi(argv[3]), cmd == "dilate"));
    }
    else if (cmd == "resize") {
        if (argc == 8 && std::string(argv[2]) == "--fx" && std::string(argv[4]) == "--fy") {
            return FilterRunner::run(argv[6], argv[7], std::make_unique<ResizeFilter>(std::stod(argv[3]), std::stod(argv[5])));
        }
        else if (argc == 8 && std::string(argv[2]) == "--width" && std::string(argv[4]) == "--height") {
            return FilterRunner::run(argv[6], argv[7], std::make_unique<ResizeFilter>(std::stoi(argv[3]), std::stoi(argv[5])));
        }
        else return (print_usage(), 1);
    }
    else if (cmd == "canny") {
        if (argc != 8) return (print_usage(), 1);
        return FilterRunner::run(argv[5], argv[6], std::make_unique<CannyFilter>(std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4])));
    }
    else if (cmd == "face_detect") {
        if (argc != 4) return (print_usage(), 1);
        return FilterRunner::run(argv[2], argv[3], std::make_unique<FaceDetectFilter>());
    }
    else if (cmd == "face_blur") {
        if (argc != 4) return (print_usage(), 1);
        return FilterRunner::run(argv[2], argv[3], std::make_unique<FaceBlurFilter>());
    }
    else if (cmd == "stitch") {
        if (argc < 5) return (print_usage(), 1);
        std::vector<std::string> imgs(argv + 2, argv + argc - 1);
        return StitchFilter::stitchImages(imgs, argv[argc - 1]) ? 0 : 1;
    }
    else if (cmd == "bgsubtract") {
        BgSubtract::Config config;
        std::vector<std::string> args(argv + 2, argv + argc);
        for (size_t i = 0; i < args.size(); ++i) {
            if (args[i] == "--varthresh") config.varThreshold = std::stod(args[++i]);
            else if (args[i] == "--history") config.history = std::stoi(args[++i]);
            else if (args[i] == "--noshadows") config.keepOnlyPureForeground = true;
            else if (config.inputVideoPath.empty()) config.inputVideoPath = args[i];
            else config.outputVideoPath = args[i];
        }
        return BgSubtract::process(config) ? 0 : 1;
    }
    else if (cmd == "video") {
        if (argc != 6 || std::string(argv[2]) != "--beta") return (print_usage(), 1);
        VideoBrightnessProcessor::Config config{ std::stoi(argv[3]), argv[4], argv[5] };
        return VideoBrightnessProcessor::applyBrightness(config) ? 0 : 1;
    }

    std::cerr << "Unknown command: " << cmd << "\n";
    print_usage();
    return 1;
}
