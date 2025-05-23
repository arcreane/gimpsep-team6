#include "video.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

namespace video {
    int run(int argc, char** argv) {
        if (argc < 5 || std::string(argv[2]) != "--beta") {
            std::cerr << "Usage: video --beta <value> in.mp4 out.mp4" << std::endl;
            return 1;
        }
        int beta = std::stoi(argv[3]);
        cv::VideoCapture cap(argv[4]);
        if (!cap.isOpened()) {
            std::cerr << "Error: cannot open video " << argv[4] << std::endl;
            return 1;
        }
        int w = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
        int h = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
        double fps = cap.get(cv::CAP_PROP_FPS);
        cv::VideoWriter writer(
            argv[5],
            cv::VideoWriter::fourcc('m', 'p', '4', 'v'),
            fps,
            cv::Size(w, h)
        );
        if (!writer.isOpened()) {
            std::cerr << "Error: cannot open writer for " << argv[5] << std::endl;
            return 1;
        }
        cv::Mat frame;
        while (cap.read(frame)) {
            cv::Mat tmp;
            frame.convertTo(tmp, -1, 1.0, beta);
            writer.write(tmp);
        }
        return 0;
    }
} // namespace video