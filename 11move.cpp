#include <opencv2/highgui.hpp>

using namespace cv;

void main() {
	Mat src = imread("Mandrill_g.bmp", IMREAD_GRAYSCALE);
	Mat dst = Mat::zeros(src.size(), src.type());
	int const delta = 150;

	for (int i = 0; i< src.rows; i++)
		for (int j = 0; j < src.cols; j++) {
			if (i - 100 > -1 && j - 150 > -1)
				dst.at<uchar>(i, j) = src.at<uchar>(i - 100, j - 150);
			else
				dst.at<uchar>(i, j) = 0;
		}

	imshow("extension", dst);
	waitKey(0);
}