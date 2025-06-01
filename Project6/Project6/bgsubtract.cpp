#include "BgSubtract.hpp"
#include "img_io.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

bool BgSubtract::process(const Config& config) {
    cv::VideoCapture cap;
    bool isCamera = false;
    int cameraId = -1;

    std::cout << "[Debug] Input video path: '" << config.inputVideoPath << "'" << std::endl;

    // Vérifier si inputVideoPath est un nombre (ID de caméra)
    if (!config.inputVideoPath.empty() &&
        std::all_of(config.inputVideoPath.begin(), config.inputVideoPath.end(),
                    [](unsigned char c){ return std::isdigit(c); })) {
        try {
            cameraId = std::stoi(config.inputVideoPath);
            isCamera = true;
        } catch (const std::invalid_argument& ia) {
            std::cerr << "[Debug] std::stoi invalid_argument: " << ia.what() << " for input: " << config.inputVideoPath << std::endl;
            isCamera = false;
        } catch (const std::out_of_range& oor) {
            std::cerr << "[Debug] std::stoi out_of_range: " << oor.what() << " for input: " << config.inputVideoPath << std::endl;
            isCamera = false;
        }
    }

    std::cout << "[Debug] isCamera: " << (isCamera ? "true" : "false") << ", cameraId: " << cameraId << std::endl;

    if (isCamera) {
        cap.open(cameraId);
        std::cout << "Info: Attempting to open camera with ID: " << cameraId << std::endl;
    } else {
        std::cout << "Info: Attempting to open video file: " << config.inputVideoPath << std::endl;
        cap.open(config.inputVideoPath);
    }

    if (!cap.isOpened()) {
        if (isCamera) {
            std::cerr << "Error: Cannot open camera with ID " << cameraId << std::endl;
        } else {
            std::cerr << "Error: Cannot open video " << config.inputVideoPath << std::endl;
        }
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

        // Afficher le résultat et vérifier si une touche est pressée pour quitter
        cv::imshow("Background Subtraction - Press Q or ESC to quit", result);
        char key = (char)cv::waitKey(1);
        if (key == 'q' || key == 'Q' || key == 27) { // 27 est le code ASCII pour ESC
            std::cout << "Arrêt demandé par l'utilisateur." << std::endl;
            break;
        }

        if (++frameCount % 100 == 0) {
            std::cout << "Processed " << frameCount << " frames." << std::endl;
        }
    }

    cap.release();
    writer.release();
    cv::destroyAllWindows(); // Fermer toutes les fenêtres OpenCV
    std::cout << "Output saved to: " << outPath << std::endl;
    return true;
}
