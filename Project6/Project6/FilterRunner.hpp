// FilterRunner.hpp
#ifndef FILTER_RUNNER_HPP
#define FILTER_RUNNER_HPP

#include "AbstractFilter.hpp"
#include "img_io.hpp"
#include <opencv2/opencv.hpp>
#include <memory>
#include <string>

class FilterRunner {
public:
    static int run(const std::string& inputPath, const std::string& outputPath, std::unique_ptr<AbstractFilter> filter);
};

#endif
