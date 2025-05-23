#pragma once

namespace resize {
    // Usage: mini-gimp resize --fx <f> --fy <f> in.jpg out.jpg
    //    or: mini-gimp resize --width <w> --height <h> in.jpg out.jpg
    int run(int argc, char** argv);
}