#ifndef STITCH_FILTER_HPP
#define STITCH_FILTER_HPP

#include <string>
#include <vector>

class StitchFilter {
public:
    static bool stitchImages(const std::vector<std::string>& inputPaths, const std::string& outputPath);
};

#endif
