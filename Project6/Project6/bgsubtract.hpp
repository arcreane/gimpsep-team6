#ifndef BGSUBTRACT_HPP
#define BGSUBTRACT_HPP

#include <string>

class BgSubtract {
public:
    struct Config {
        double varThreshold = 16.0;
        int history = 500;
        bool detectShadows = true;
        bool keepOnlyPureForeground = false;
        std::string inputVideoPath;
        std::string outputVideoPath;
    };

    static bool process(const Config& confisg);
};
#endif
