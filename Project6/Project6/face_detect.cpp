#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include "face_detect.h"

namespace face_detect {

    int run(int argc, char** argv) {
        if (argc < 4) {
            std::cerr << "Usage: face_detect in.jpg out.jpg\n";
            return 1;
        }

        std::string inputPath = argv[2];     // attention ! argv[2] car argv[1] = "face_detect"
        std::string outputPath = argv[3];

        cv::Mat img = cv::imread(inputPath);
        if (img.empty()) {
            std::cerr << "Erreur de lecture : " << inputPath << "\n";
            return 1;
        }

        cv::CascadeClassifier face_cascade;
        if (!face_cascade.load("haarcascade_frontalface_default.xml")) {
            std::cerr << "Erreur chargement du modèle Haar.\n";
            return 1;
        }

        cv::Mat gray;
        cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray, gray);

        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(gray, faces);

        for (const auto& face : faces) {
            cv::rectangle(img, face, cv::Scalar(0, 255, 0), 2);
        }

        cv::imwrite(outputPath, img);
        std::cout << "Visages détectés et image sauvegardée.\n";

        return 0;
    }

}  // namespace face_detect
