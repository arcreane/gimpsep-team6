// main.cpp
#include <iostream>
#include <string>

#include "img_io.hpp"
#include "brightness.hpp"
#include "morphology.hpp"
#include "resize.hpp"
#include "stitch.hpp"
#include "canny.hpp"
#include "video.hpp"
#include "grayscale.hpp"
#include "blur.hpp"
#include "bgsubtract.hpp"
#include "panorama.h"
#include "face_detect.h"
#include "face_blur.h"



static void print_usage() {
    std::cerr << "Usage: mini-gimp <command> [options] <input> [<input2> �] <output>\n\n"
        << "Commands:\n"
        << "  brightness --beta <value>      in.jpg out.jpg\n"
        << "  dilate     --size <value>      in.jpg out.jpg\n"
        << "  erode      --size <value>      in.jpg out.jpg\n"
        << "  resize     (--fx <f> --fy <f> | --width <w> --height <h>)  in.jpg out.jpg\n"
        << "  stitch     <img1> <img2> [<img3> �] out.jpg\n"
        << "  canny      --th1 <t1> --th2 <t2> --kernel <k>  in.jpg out.png\n"
        << "  video      --beta <value>      in.mp4 out.mp4\n"
        << "  grayscale  in.jpg out.jpg\n"
        << "  blur       --ksize <value>   in.jpg out.jpg\n"
        << "  bgsubtract [opts] <in_vid> <out_vid.avi>\n"
        << "  panorama   <img1> <img2> [<img3> …] out.jpg\n"
        << "  face_detect in.jpg out.jpg     (détection de visages)\n"
        << "  face_blur   in.jpg out.jpg      (floute les visages détectés)\n"
        << "  -h, --help    Show this help message\n";
}

int main(int argc, char** argv) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    std::string cmd = argv[1];
    if (cmd == "-h" || cmd == "--help") {
        print_usage();
        return 0;
    }
    else if (cmd == "brightness") {
        return brightness::run(argc, argv);
    }
    else if (cmd == "dilate") {
        return morphology::run(argc, argv, true);
    }
    else if (cmd == "erode") {
        return morphology::run(argc, argv, false);
    }
    else if (cmd == "resize") {
        return resize::run(argc, argv);
    }
    else if (cmd == "stitch") {
        return stitch::run(argc, argv);
    }
    else if (cmd == "canny") {
        return canny::run(argc, argv);
    }
    else if (cmd == "video") {
        return video::run(argc, argv);
    }
    else if (cmd == "grayscale") {
        return grayscale::run(argc, argv);
    }
    else if (cmd == "blur") {
        return blur::run(argc, argv);
    }
    else if (cmd == "bgsubtract") {
        return bgsubtract::run(argc, argv);
    }
    else if (cmd == "panorama") {
        return panorama::run(argc, argv);
    }
    else if (cmd == "face_detect") {
        return face_detect::run(argc, argv);
    }
    else if (cmd == "face_blur") {
        return face_blur::run(argc, argv);
    }


    else {
        std::cerr << "Error: Unknown command \"" << cmd << "\"\n\n";
        print_usage();
        return 1;
    }
}
