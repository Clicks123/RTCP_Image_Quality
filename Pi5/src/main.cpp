#include <iostream>
#include "opencv4/opencv2/opencv.hpp"
//note must build file using termnial 
/*

    1) go into Pi5 directory in terminal
    2) type $cmake .
    3)once cmake compiles without error type $make
    4) this step changes with version
        -basic test type $./DisplayImage cat.jpg

*/

#include <stdio.h>
 
using namespace cv;
 
int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
 
    Mat image;
    image = imread( argv[1], IMREAD_COLOR );
 
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
 
    waitKey(0);
 
    return 0;
}