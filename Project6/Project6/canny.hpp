#pragma once

namespace canny {
    // Usage: mini-gimp canny --th1 <t1> --th2 <t2> --kernel <k> in.jpg out.png
    int run(int argc, char** argv);
}