#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int lowThreshold = 50;
const int max_lowThreshold = 100;
const int cannyRatio = 3;
const int kernel_size = 3;

void on_trackbar(int, void*) {}

int main(int argc, char** argv)
{
    VideoCapture cap(0);
    if(!cap.isOpened())
    {
        cout << "Error: No se pudo abrir la cámara" << endl;
        return -1;
    }

    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Canny Edge", WINDOW_AUTOSIZE);

    createTrackbar("Threshold", "Canny Edge", &lowThreshold, max_lowThreshold, on_trackbar);

    Mat frame, gray, detectedEdges;

    while(true)
    {
        bool success = cap.read(frame);
        if(!success)
        {
            cout << "Error: No se pudo leer un frame del video" << endl;
            break;
        }

        cvtColor(frame, gray, COLOR_BGR2GRAY);
        blur(gray, detectedEdges, Size(3,3));
        Canny(detectedEdges, detectedEdges, lowThreshold, lowThreshold * cannyRatio, kernel_size);

        imshow("Original", frame);
        imshow("Canny Edge", detectedEdges);

        char key = (char)waitKey(30);
        if(key == 27)
        {
            break;
        }
    }

    cap.release();
    destroyAllWindows();
    return 0;
}
