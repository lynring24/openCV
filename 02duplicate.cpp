#include <opencv2/highgui.hpp>

using namespace cv;

void main() {
	Mat src = imread("Mandrill.bmp", IMREAD_COLOR);
	Mat dst = Mat::zeros(src.size(), src.type());
	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++)
			for (int c = 0; c < 3; c++)
				dst.at<Vec3b>(i, j)[c] = src.at<Vec3b>(i, j)[c];

	imshow("영상보기", dst);
	waitKey(0);
}