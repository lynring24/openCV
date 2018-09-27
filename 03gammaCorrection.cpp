#include <opencv2/highgui.hpp>
#include <math.h>

using namespace cv;

void main() {
	Mat src = imread("citrus.bmp", IMREAD_GRAYSCALE);
	Mat dst = Mat::zeros(src.size(), src.type());
	double k, convert;

	imshow("원본", src);
	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++) {
			k = src.at<uchar>(i, j)/255.0;
			convert = pow(k, 0.5);
			dst.at<uchar>(i, j) = 255 * convert;
		}

	imshow("histogram equalization 결과", dst);
	waitKey(0);
}