#include <iostream>
#include "opencv4/opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/stitching.hpp>
//#include <opencv/opencv_contrib-4.x/modules/xfeatures2d/include/opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d.hpp>
//#include <opencv2/xfeatures2d/nonfree.hpp>
#include <vector>
//#include "config2/cameraMatrix.xml"
//#include "config2/dist.xml"
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
void Disp2LiveWebcam(void);
void Stich2CAM(void);
int surf(void);
void detectAndComputeSURF(Mat& img, vector<KeyPoint>& keypoints, Mat& descriptors);

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;


Mat captureFrame(int cameraIndex) {
    VideoCapture cap(cameraIndex);
    if (!cap.isOpened()) {
        cerr << "Error: Failed to open camera " << cameraIndex << endl;
        return Mat();
    }

    Mat frame;
    cap >> frame;
    if (frame.empty()) {
        cerr << "Error: Failed to capture frame from camera " << cameraIndex << endl;
    }
    return frame;
}


int main(int argc, char *argv[])
{

    // Destroy the windows
    cv::destroyAllWindows();
    if(argc < 2){
        printf("USAGE: %s <argument>\n", argv[0]);
        return -1;
    }

    if(strcmp(argv[1], "IMG") == 0){
        imgDispTest();
    }
    else if(strcmp(argv[1], "CAM") == 0){
        DispLiveWebcam();
    }
    else if(strcmp(argv[1], "CAM2") == 0){
        Disp2LiveWebcam();
    }
    else if(strcmp(argv[1], "PANO") == 0){
        Stich2CAM();
    }    
    else if(strcmp(argv[1], "SURF") == 0){
        surf();
    }
    else{
        printf("Unknown argument %s\n", argv[1]);
        return 1;
    }

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

    resizeWindow("Display Image", 1280,720); //sets size to 1080p
 
        while (cv::waitKey(30) != 'q') {}
 
        cv::destroyAllWindows();

    return;
}

//outdated solution for webcam capture
void DispLiveWebcam(void){
        Mat frame;

    
    cv::VideoCapture cap(0, cv::CAP_V4L2); // Adjust the index if necessary

    cv::namedWindow("Live", cv::WINDOW_NORMAL);

    cv::resizeWindow("Live", 1920,1080);

    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open the first webcam" << std::endl;
        return;
    }
    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // show live and wait for a key with timeout long enough to show images
        imshow("Live", frame);
        if (cv::waitKey(30) == 'q') {
            break;
        }


    }
        cap.release();
        cv::destroyAllWindows();
    // the camera will be deinitialized automatically in VideoCapture destructor
    return;
}

void Disp2LiveWebcam(void){
       // Open the first webcam
    cv::VideoCapture cap1(0, cv::CAP_V4L2); // Adjust the index if necessary

    if (!cap1.isOpened()) {
        std::cerr << "Error: Could not open the first webcam" << std::endl;
        return;
    }

    // Open the second webcam
    cv::VideoCapture cap2(2, cv::CAP_V4L2); // Adjust the index if necessary
    if (!cap2.isOpened()) {
        std::cerr << "Error: Could not open the second webcam" << std::endl;
        return;
    }

    // Create windows to display the video streams
    cv::namedWindow("Webcam 1", cv::WINDOW_NORMAL);
    cv::namedWindow("Webcam 2", cv::WINDOW_NORMAL);

    cv::resizeWindow("Webcam 1", 1280,720);
    cv::resizeWindow("Webcam 2", 1280,720);

    while (true) {
        cv::Mat frame1, frame2;

        // Capture a frame from each webcam
        cap1 >> frame1;
        cap2 >> frame2;

        // Check if frames are empty
        /*if (frame1.empty() || frame2.empty()) {
            std::cerr << "Error: Could not capture frames" << std::endl;
            break;
        }*/

        // Display the frames
        cv::imshow("Webcam 1", frame1);
        cv::imshow("Webcam 2", frame2);

        // Exit the loop if 'q' is pressed
        if (cv::pollKey() == 'q') {
            break;
        }
    }

    // Release the video captures
    cap1.release();
    cap2.release();

    // Destroy the windows
    cv::destroyAllWindows();

    return;

}

void Stich2CAM(void){

        Mat fr1, fr2, pano;
    //bool try_use_gpu = true;
    vector<Mat> imgs;
    VideoCapture cap(0, cv::CAP_V4L2), cap2(2, cv::CAP_V4L2);
            cv::namedWindow("Stitched Image", cv::WINDOW_AUTOSIZE);
    while (true)
    {
        cap >> fr1;
        cap2 >> fr2;
        imgs.push_back(fr1.clone());
        imgs.push_back(fr2.clone());

        cv::Ptr<Stitcher> test = cv::Stitcher::create(cv::Stitcher::PANORAMA);
        cv::Stitcher::Status status = test->stitch(imgs, pano);

        if (status != Stitcher::OK)
        {
            cout << "Error stitching - Code: " <<int(status)<<endl;
            return;
        }

        //cv::namedWindow("Webcam 1", cv::WINDOW_NORMAL);
        //cv::namedWindow("Webcam 2", cv::WINDOW_NORMAL);


        //cv::resizeWindow("Webcam 1", 1280,720);
        //cv::resizeWindow("Webcam 2", 1280,720);
        //cv::resizeWindow("Stithed Image", 1920,1080);

        //imshow("Webcam 1", fr1);
        //imshow("Webcam 2", fr2);
        imshow("Stitched Image", pano);

        if (cv::pollKey() == 'q') {
            break;
        }

    } 
    cap.release();
    cap2.release();   
    // Destroy the windows
    cv::destroyAllWindows();
    return;
}

int surf(void){
    try {
        // Capture frames from two cameras
        Mat img1 = captureFrame(0);
        Mat img2 = captureFrame(1);

        if (img1.empty() || img2.empty()) {
            cerr << "Error: One or both images are empty." << endl;
            return -1;
        }

        // Detect features and compute descriptors using SURF
        vector<KeyPoint> keypoints1, keypoints2;
        Mat descriptors1, descriptors2;
        detectAndComputeSURF(img1, keypoints1, descriptors1);
        detectAndComputeSURF(img2, keypoints2, descriptors2);

        if (keypoints1.empty() || keypoints2.empty()) {
            cerr << "Error: No keypoints found in one or both images." << endl;
            return -1;
        }

        // Match features using BFMatcher
        BFMatcher matcher(NORM_L2);
        vector<DMatch> matches;
        matcher.match(descriptors1, descriptors2, matches);

        // Check if matches are found
        if (matches.empty()) {
            cerr << "Error: No matches found." << endl;
            return -1;
        }

        // Sort matches by distance
        sort(matches.begin(), matches.end());

        // Draw matches
        Mat imgMatches;
        drawMatches(img1, keypoints1, img2, keypoints2, matches, imgMatches);
        imshow("Matches", imgMatches);
        waitKey();

        // Use RANSAC to find a homography matrix
        vector<Point2f> pts1, pts2;
        for (const auto& match : matches) {
            pts1.push_back(keypoints1[match.queryIdx].pt);
            pts2.push_back(keypoints2[match.trainIdx].pt);
        }

        if (pts1.size() < 4 || pts2.size() < 4) {
            cerr << "Error: Not enough points for homography." << endl;
            return -1;
        }

        Mat H = findHomography(pts1, pts2, RANSAC);

        if (H.empty()) {
            cerr << "Error: Homography matrix is empty." << endl;
            return -1;
        }

        // Stitch images together
        Mat result;
        warpPerspective(img1, result, H, Size(img1.cols + img2.cols, img1.rows));
        Mat half(result, Rect(0, 0, img2.cols, img2.rows));
        img2.copyTo(half);

        imshow("Stitched Image", result);
        waitKey();

    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
        return -1;
    }

    return 0;
}


void detectAndComputeSURF(Mat& img, vector<KeyPoint>& keypoints, Mat& descriptors) {
    Ptr<SURF> detector = SURF::create(400);
    if (img.empty()) {
        cerr << "Error: Empty image passed to detectAndComputeSURF" << endl;
        return;
    }
    detector->detectAndCompute(img, noArray(), keypoints, descriptors);
}