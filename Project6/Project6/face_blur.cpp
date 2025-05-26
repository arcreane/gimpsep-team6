#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include "face_blur.h"

namespace face_blur {

    int run(int argc, char** argv) {
        if (argc < 4) {
            std::cerr << "Usage: face_blur in.jpg out.jpg\n";
            return 1;
        }

        std::string inputPath = argv[2]; // argv[1] = face_blur
        std::string outputPath = argv[3];

        // Chargement de l'image
        cv::Mat image = cv::imread(inputPath);
        if (image.empty()) {
            std::cerr << "Erreur lors du chargement de l'image : " << inputPath << "\n";
            return 1;
        }

        // Chargement du classificateur
        cv::CascadeClassifier face_cascade;
        if (!face_cascade.load("haarcascade_frontalface_default.xml")) {
            std::cerr << "Erreur lors du chargement du modèle Haar\n";
            return 1;
        }

        // Conversion en niveaux de gris
        cv::Mat gray;
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray, gray);

        // Détection des visages
        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(gray, faces);

        // Floutage de chaque visage
        for (const auto& face : faces) {
            cv::Mat roi = image(face); // zone du visage
            cv::GaussianBlur(roi, roi, cv::Size(45, 45), 30); // flou gaussien
        }

        cv::imwrite(outputPath, image);
        cv::imshow("Visages floutés", image);
        cv::waitKey(0);

        return 0;
    }

}
