#include <iostream>
#include "opencv4/opencv2/opencv.hpp"
using namespace cv;
int main()
{

    std::string image_path = "/home/5team4/Documents/RTCP/RTCP_Image_Quality/cat.jpg";
    Mat img = imread(image_path, IMREAD_COLOR);

    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    return 0;
}
///usr/include/opencv4/opencv2/core/neon_utils.hpp