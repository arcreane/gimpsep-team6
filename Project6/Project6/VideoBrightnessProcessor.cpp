#include "VideoBrightnessProcessor.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

bool VideoBrightnessProcessor::applyBrightness(const Config& config) {
    cv::VideoCapture cap(config.inputPath);
    if (!cap.isOpened()) {
        std::cerr << "Error: Cannot open video " << config.inputPath << std::endl;
        return false;
    }

    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    double fps = cap.get(cv::CAP_PROP_FPS);

    cv::VideoWriter writer(
        config.outputPath,
        cv::VideoWriter::fourcc('m', 'p', '4', 'v'),
        fps,
        cv::Size(width, height)
    );

    if (!writer.isOpened()) {
        std::cerr << "Error: Cannot open writer for " << config.outputPath << std::endl;
        return false;
    }

    cv::Mat frame;
    while (cap.read(frame)) {
        cv::Mat tmp;
        frame.convertTo(tmp, -1, 1.0, config.beta);
        writer.write(tmp);
    }

    return true;
}