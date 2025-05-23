#pragma once

namespace morphology {
    // Usage: mini-gimp dilate --size <n> in.jpg out.jpg
    //        mini-gimp erode  --size <n> in.jpg out.jpg
    // `dilateFlag` == true for dilation, false for erosion
    int run(int argc, char** argv, bool dilateFlag);
}