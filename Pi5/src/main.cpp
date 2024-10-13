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
void DispLiveWebcam(void);

using namespace cv;
using namespace std;

int main(void)
{
       // Open the first webcam
    cv::VideoCapture cap1(0); // Adjust the index if necessary
    if (!cap1.isOpened()) {
        std::cerr << "Error: Could not open the first webcam" << std::endl;
        return -1;
    }

    // Open the second webcam
    cv::VideoCapture cap2(2); // Adjust the index if necessary
    if (!cap2.isOpened()) {
        std::cerr << "Error: Could not open the second webcam" << std::endl;
        return -1;
    }

    // Create windows to display the video streams
    cv::namedWindow("Webcam 1", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Webcam 2", cv::WINDOW_AUTOSIZE);

    while (true) {
        cv::Mat frame1, frame2;

        // Capture a frame from each webcam
        cap1 >> frame1;
        cap2 >> frame2;

        // Check if frames are empty
        if (frame1.empty() || frame2.empty()) {
            std::cerr << "Error: Could not capture frames" << std::endl;
            break;
        }

        // Display the frames
        cv::imshow("Webcam 1", frame1);
        cv::imshow("Webcam 2", frame2);

        // Exit the loop if 'q' is pressed
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }

    // Release the video captures
    cap1.release();
    cap2.release();

    // Destroy the windows
    cv::destroyAllWindows();


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
    
    
    namedWindow("Display Image", WINDOW_NORMAL );//gets display window & names it Display Image
     imshow("Display Image", image); //shows display window

    resizeWindow("Display Image", 1920,1080); //sets size to 1080p
 
    waitKey(0);

    return;
}

void DispLiveWebcam(void){
        Mat frame0;
        Mat frame1;
    //--- INITIALIZE VIDEOCAPTURE
    VideoCapture cap;
    // open the default camera using default API
    cap.open(0);
    // OR advance usage: select any API backend
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID + apiID);
    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return;
    }
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl;
    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame0);
        // check if we succeeded
        if (frame0.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // show live and wait for a key with timeout long enough to show images
        imshow("Live", frame0);
        if (waitKey(5) >= 0)
            break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return;
}