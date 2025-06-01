#include "FaceDetectFilter.hpp"

std::vector<cv::Rect> FaceDetectFilter::detectFaces(const cv::Mat& input) {
    std::vector<cv::Rect> faces;
    cv::CascadeClassifier face_cascade;
    face_cascade.load("haarcascade_frontalface_default.xml");

    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(gray, gray);
    face_cascade.detectMultiScale(gray, faces);
    return faces;
}

void FaceDetectFilter::apply(const cv::Mat& input, cv::Mat& output) {
    output = input.clone();
    auto faces = detectFaces(input);
    for (const auto& face : faces) {
        cv::rectangle(output, face, cv::Scalar(0, 255, 0), 2);
    }
}
