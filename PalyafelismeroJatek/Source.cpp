#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <iostream>
using namespace cv;
using namespace std;
void drawShape(Mat* img, std::vector<cv::Point> approx, Scalar color)
{
	int count = approx.size();
	for (size_t i = 0; i < count; i++)
	{
		if (i != count - 1)
			line(*img, approx[i], approx[i + 1], color, 10, 8);
		else line(*img, approx[i], approx[0], color, 10, 8);
	}

}

int main(int args, const char** argv) {
	Mat img = imread("C:\\Users\\Balint\\Pictures\\palya.jpg", CV_LOAD_IMAGE_UNCHANGED);
	if (img.empty()) {
		cout << "Error: Image cannot be loaded..." << endl;
		return -1;
	}

	Mat src;
	img.copyTo(src);
	cv::Mat grayScaled;
	cv::Mat thresholded;
	cvtColor(src, grayScaled, CV_BGR2GRAY);
	//thresholding
	threshold(grayScaled, thresholded, 120, 255, CV_THRESH_BINARY);

	// Find contours
	std::vector<std::vector<cv::Point> > contours;
	cv::findContours(thresholded.clone(), contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	Mat dst;
	img.copyTo(dst);

	std::vector<cv::Point> approx;
	for (int i = 0; i < contours.size(); i++)
	{
		cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.025, true);

		if (std::fabs(cv::contourArea(contours[i])) < 200)// || !cv::isContourConvex(approx))
			continue;

		if (approx.size() == 4 && approx.size() <= 14)
		{
			drawShape(&dst, approx, Scalar(110, 220, 0));
		}

	}

	//cv::Mat dst = src.clone();

	namedWindow("MYWINDOW", CV_WINDOW_KEEPRATIO);
	imshow("MYWINDOW", dst);

	namedWindow("Source", CV_WINDOW_KEEPRATIO);
	imshow("Source", src);
	namedWindow("Thresholded", CV_WINDOW_KEEPRATIO);
	imshow("Thresholded", thresholded);
	waitKey(0);
	destroyWindow("MYWINDOW");
	return 0;
}