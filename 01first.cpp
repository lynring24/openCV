#include <opencv2/highgui.hpp>

using namespace cv;

void main() {
	Mat image = imread("Mandrill.bmp", IMREAD_COLOR);
	cv::imshow("���󺸱�", image);
	cv::waitKey(0);
}