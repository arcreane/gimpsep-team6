#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    string imageName = "C:\\Users\\louis\\Desktop\\A2\\Multimedia\\Project\\gimpsep-team6\\Project6\\x64\\Debug\\imagetest.jpeg"; 
    if (argc > 1) {
        imageName = argv[1];
    }

    Mat image = imread(imageName, IMREAD_COLOR);

    // Check if image was loaded successfully
    if (image.empty()) {
        cerr << "Error: Could not open or find the image!" << endl;
        return -1;
    }

    namedWindow("Display Window", WINDOW_AUTOSIZE);
    imshow("Display Window", image);

    waitKey(0);
    return 0;
}