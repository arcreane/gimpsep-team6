#include "FilterRunner.hpp"
#include "img_io.hpp"

int FilterRunner::run(const std::string& inputPath, const std::string& outputPath,
    std::unique_ptr<AbstractFilter> filter) {
    cv::Mat input = loadOrExit(inputPath);
    cv::Mat output;
    filter->apply(input, output);
    saveOrExit(outputPath, output);
    return 0;
}
