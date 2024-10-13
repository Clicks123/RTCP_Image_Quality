#include <iostream>
#include "opencv4/opencv2/opencv.hpp"
//note must build file using termnial 
/*

    1) go into Pi5 directory in terminal
    2) type $cmake .
    3)once cmake compiles without error type $make
    4) this step changes with version
        -basic test type $./output

*/

#include <stdio.h>

void imgDispTest(void);

using namespace cv;
 
int main(void)
{
 
    imgDispTest();
 
    return 0;
}

//displays an image for a test
void imgDispTest(void){

    std::string imagePath = "/home/5team4/Documents/RTCP/RTCP_Image_Quality/Pi5/catv2.png";
    Mat image;
    image = imread( imagePath, IMREAD_COLOR );
 
    if ( !image.data )
    {
        printf("No image data \n");
        return;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
 
    waitKey(0);

    return;
}