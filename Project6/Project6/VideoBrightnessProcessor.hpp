#ifndef VIDEO_BRIGHTNESS_PROCESSOR_HPP
#define VIDEO_BRIGHTNESS_PROCESSOR_HPP

#include <string>

class VideoBrightnessProcessor {
public:
    struct Config {
        int beta;
        std::string inputPath;
        std::string outputPath;
    };

    static bool applyBrightness(const Config& config);
};

#endif
