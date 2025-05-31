#include "annotate.hpp"
#include "../img_io.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>

namespace annotate {

    static bool parseColor(const std::string& s, cv::Scalar& col) {
        // expect "B,G,R"
        int b, g, r;
        char c1, c2;
        std::istringstream iss(s);
        if (!(iss >> b >> c1 >> g >> c2 >> r) || c1 != ',' || c2 != ',')
            return false;
        col = cv::Scalar(b, g, r);
        return true;
    }

    int run(int argc, char** argv) {
        if (argc < thirteen) {
            std::cerr << "Usage: text --text <str> --x <px> --y <px> "
                << "--scale <f> --color B,G,R --thickness <t> in.jpg out.jpg\n";
            return 1;
        }

        std::string txt;
        int x = 0, y = 0;
        double scale = 1.0;
        cv::Scalar color(255, 255, 255);
        int thickness = 1;

        // Simple linear parse
        for (int i = 2; i + 1 < argc && argv[i][0] == '-'; i += 2) {
            std::string opt = argv[i];
            std::string val = argv[i + 1];
            if (opt == "--text")     txt = val;
            else if (opt == "--x")   x = std::stoi(val);
            else if (opt == "--y")   y = std::stoi(val);
            else if (opt == "--scale")  scale = std::stod(val);
            else if (opt == "--color") {
                if (!parseColor(val, color)) {
                    std::cerr << "Bad color format, use B,G,R\n"; return 1;
                }
            }
            else if (opt == "--thickness") thickness = std::stoi(val);
            else {
                std::cerr << "Unknown option " << opt << "\n"; return 1;
            }
        }

        // last two args are input and output
        std::string in = argv[argc - 2];
        std::string out = argv[argc - 1];

        cv::Mat img = loadOrExit(in);

        // draw the text
        int fontFace = cv::FONT_HERSHEY_SIMPLEX;
        cv::putText(
            img,
            txt,
            cv::Point(x, y),
            fontFace,
            scale,
            color,
            thickness,
            cv::LINE_AA
        );

        saveOrExit(out, img);
        return 0;
    }

} // namespace annotate
