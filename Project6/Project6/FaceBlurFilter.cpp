#include "FaceBlurFilter.hpp"
#include "FaceDetectFilter.hpp"

void FaceBlurFilter::apply(const cv::Mat& input, cv::Mat& output) {
    output = input.clone();
    FaceDetectFilter detector;
    auto faces = detector.detectFaces(input);

    for (const auto& face : faces) {
        cv::GaussianBlur(output(face), output(face), cv::Size(45, 45), 30);
    }
}
