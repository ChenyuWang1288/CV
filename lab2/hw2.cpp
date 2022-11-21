#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main(int argc, char** argv) {
	string filename;
	std::cout << "Please input your image name: " << endl;
	std::cin >> filename;
	Mat img = imread(filename, IMREAD_GRAYSCALE);
	Mat imgRGB = imread(filename);
	Canny(img, img, 32, 128);
	int key;
	vector<vector<Point>> edge;
	Scalar note = Scalar(0, 255, 0);
	findContours(img, edge, RETR_TREE, CHAIN_APPROX_SIMPLE);
	int counter = 0;
	for (auto& i : edge) {
		if (i.size() >= 15) {
			RotatedRect res = fitEllipse(i);
			ellipse(imgRGB, res, note, 1, LINE_AA);
			counter++;
		}
	}
	imshow("demo1", imgRGB);
	key = waitKey(0);
	imwrite("result.png", imgRGB);
	
	return 0;
} 