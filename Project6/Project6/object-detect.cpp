#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include "object_detect.h"

namespace object_detect {

    int run(int argc, char** argv) {
        if (argc < 5) {
            std::cerr << "Usage: object_detect <cascade_model.xml> in.jpg out.jpg\n";
            return 1;
        }

        std::string modelPath = argv[2];
        std::string inputPath = argv[3];
        std::string outputPath = argv[4];

        cv::Mat image = cv::imread(inputPath);
        if (image.empty()) {
            std::cerr << "Erreur : image non chargée.\n";
            return 1;
        }

        cv::CascadeClassifier classifier;
        if (!classifier.load(modelPath)) {
            std::cerr << "Erreur : modèle Haar introuvable.\n";
            return 1;
        }

        cv::Mat gray;
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray, gray);

        std::vector<cv::Rect> objects;
        classifier.detectMultiScale(gray, objects);

        for (const auto& obj : objects) {
            cv::rectangle(image, obj, cv::Scalar(0, 0, 255), 2);
        }

        cv::imwrite(outputPath, image);
        cv::imshow("Objets détectés", image);
        cv::waitKey(0);

        return 0;
    }

}
