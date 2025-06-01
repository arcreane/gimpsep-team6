#ifndef MORPHOLOGY_FILTER_HPP
#define MORPHOLOGY_FILTER_HPP

#include "AbstractFilter.hpp"

class MorphologyFilter : public AbstractFilter {
private:
    int size;
    bool dilateFlag;

public:
    MorphologyFilter(int size, bool dilateFlag);
    void apply(const cv::Mat& input, cv::Mat& output) override;
};

#endif 