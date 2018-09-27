#include <opencv2/highgui.hpp>

using namespace cv;

void main() {
	Mat src = imread("Mandrill_g.bmp", IMREAD_GRAYSCALE);
	Mat dst = Mat::zeros(src.size(), src.type());
	int Ep = -1, Eg = -1, T = -1, threshold = 120;

	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++) {
			Ep = Eg;
			T = src.at<uchar>(i, j) + Ep;
			if (T > threshold) {
				dst.at<uchar>(i, j) = 255;
				Eg = T - 2 * threshold;
			}
			else {
				dst.at<uchar>(i, j) = 0;
				Eg = threshold;
			}	
		}	
	imshow("영상보기", dst);
	waitKey(0);
}