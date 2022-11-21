#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
double fps;
double height;
double width;
void drawBeginning(VideoWriter& writer) {
    Mat imag(Size(width, height), CV_8UC3, Scalar(0, 0, 0));
    putText(imag, "This is the begin", cv::Point(50,300), FONT_HERSHEY_COMPLEX, 2, Scalar(0, 255, 0), 2);
    putText(imag, "3200102324 WangChenyu", cv::Point(30, 520), FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(200, 200, 250), 1, 0);

    for (int i = 0; i < 2*fps; i++) {
        writer << imag;
    }
}
int main(int argc, char** argv) {
    string filepath(argv[1]);
    Mat img;
    int i = 1;
    // read in video
    VideoCapture capture(filepath + "/test.avi");
    if (!capture.isOpened()) {
        cout << "Error opening video stream or file" << endl;
    }
    else {
        fps = capture.get(CAP_PROP_FPS);
        height = capture.get(CAP_PROP_FRAME_HEIGHT);
        width = capture.get(CAP_PROP_FRAME_WIDTH);
    }
    // initialize video
    VideoWriter writer;
    Size videoSize = Size(width, height);
    writer = VideoWriter("out.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, videoSize);
    drawBeginning(writer);
    // read in images
    while (1) {
        string imagepath = filepath + "/test" + to_string(i) + ".jpg";
        i++;
        img = imread(imagepath);
        if (img.data == 0) {
            break;
        }
        Mat after;
        resize(img, after, videoSize);
        putText(after, "3200102324 WangChenyu", cv::Point(30, 520), FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(200, 200, 250), 1, 0);
        for (int j = 0; j < 60; j++) {
            writer.write(after);
        }
    }
    Mat frame;
    if (!capture.isOpened()) {
        cout << "Error opening video stream or file" << endl;
    }
    else while(1) {
        capture >> frame;
        if (frame.empty())
            break;
        putText(frame, "3200102324 WangChenyu", cv::Point(30, 520), FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(200, 200, 250), 1, 0);
        writer.write(frame);
    }
    writer.release();
    return 0;
}