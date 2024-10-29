#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

// Function to split and resize the image for multiple projectors, maintaining aspect ratio
vector<Mat> splitImageForProjectors(const Mat& image, int projectors = 3, int screenWidth = 1920, int screenHeight = 1080) {
    int imageHeight = image.rows;
    int imageWidth = image.cols;

    // Calculate the width of each part of the image for the projectors
    int splitWidth = imageWidth / projectors;
    vector<Mat> splits;

    for (int i = 0; i < projectors; ++i) {
        // Calculate the x-axis bounds for each split
        int startX = i * splitWidth;
        int endX = (i != projectors - 1) ? (startX + splitWidth) : imageWidth;

        // Crop the image for the current projector
        Mat splitImage = image(Rect(startX, 0, endX - startX, imageHeight));

        // Create a black canvas (background) of 1920x1080 to paste the image onto
        Mat canvas(screenHeight, screenWidth, CV_8UC3, Scalar(0, 0, 0));

        // Get the aspect ratios of the image and the projector screen
        double imageAspectRatio = static_cast<double>(splitImage.cols) / splitImage.rows;
        double screenAspectRatio = static_cast<double>(screenWidth) / screenHeight;

        int newWidth, newHeight;

        // Determine whether to fit the image based on width or height
        if (imageAspectRatio > screenAspectRatio) {
            // Image is wider than the screen, fit to width
            newWidth = screenWidth;
            newHeight = static_cast<int>(newWidth / imageAspectRatio);
        } else {
            // Image is taller than the screen, fit to height
            newHeight = screenHeight;
            newWidth = static_cast<int>(newHeight * imageAspectRatio);
        }

        // Resize the split image to the new dimensions
        Mat splitImageResized;
        resize(splitImage, splitImageResized, Size(newWidth, newHeight), 0, 0, INTER_AREA);

        // Calculate the padding to center the image on the black canvas
        int xOffset = (screenWidth - newWidth) / 2;
        int yOffset = (screenHeight - newHeight) / 2;

        // Place the resized image onto the black canvas, centered
        splitImageResized.copyTo(canvas(Rect(xOffset, yOffset, newWidth, newHeight)));

        splits.push_back(canvas);
    }

    return splits;
}

int main() {
    // Load the image
    string imagePath = "apple.png";
    Mat image = imread(imagePath);

    // Check if the image was loaded correctly
    if (image.empty()) {
        cout << "Error loading image" << endl;
        return -1;
    }

    // Split the image for the projectors
    vector<Mat> projectorSplits = splitImageForProjectors(image, 3, 1920, 1080);

    // Display each split image in separate windows using cv::imshow()
    for (size_t i = 0; i < projectorSplits.size(); ++i) {
        string windowName = "Projector " + to_string(i + 1);
        imshow(windowName, projectorSplits[i]);
    }

    // Wait for a key press and close all windows
    waitKey(0);
    destroyAllWindows();

    return 0;
}
