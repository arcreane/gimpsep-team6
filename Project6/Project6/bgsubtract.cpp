#include "BgSubtract.hpp"
#include "img_io.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>

bool BgSubtract::process(const Config& config) {
    cv::VideoCapture cap(config.inputVideoPath);
    if (!cap.isOpened()) {
        std::cerr << "Error: Cannot open video " << config.inputVideoPath << std::endl;
        return false;
    }

    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    double fps = cap.get(cv::CAP_PROP_FPS);

    std::string outPath = config.outputVideoPath;
    if (outPath.length() < 4 || outPath.substr(outPath.length() - 4) != ".avi") {
        outPath += ".avi";
        std::cout << "Info: Forcing .avi output extension: " << outPath << std::endl;
    }

    cv::VideoWriter writer(outPath, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(width, height));
    if (!writer.isOpened()) {
        std::cerr << "Error: Cannot open writer for " << outPath << std::endl;
        return false;
    }

    cv::Ptr<cv::BackgroundSubtractorMOG2> subtractor =
        cv::createBackgroundSubtractorMOG2(config.history, config.varThreshold, config.detectShadows);

    cv::Mat frame, fgMask, cleaned, result;
    int frameCount = 0;

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        subtractor->apply(frame, fgMask);
        cleaned = fgMask.clone();

        if (config.detectShadows && config.keepOnlyPureForeground) {
            cv::threshold(fgMask, cleaned, 254, 255, cv::THRESH_BINARY);
        }

        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
        cv::morphologyEx(cleaned, cleaned, cv::MORPH_OPEN, kernel);

        result = cv::Mat::zeros(frame.size(), frame.type());
        frame.copyTo(result, cleaned);

        writer.write(result);
        if (++frameCount % 100 == 0) {
            std::cout << "Processed " << frameCount << " frames." << std::endl;
        }
    }

    cap.release();
    writer.release();
    std::cout << "Output saved to: " << outPath << std::endl;
    return true;
}
