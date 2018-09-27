#include <opencv2/highgui.hpp>

using namespace cv;

void main() {
	Mat src = imread("citrus.bmp", IMREAD_GRAYSCALE);
	Mat dst = Mat::zeros(src.size(), src.type());
	int histogram[256] = { 0, };
	int value;
	int aug_histogram[256]={ 0, };
	int sum = 0;
	double Dm = 255;
	double area = src.rows*src.cols;

	imshow("원본",src);
	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++) {
			value = src.at<uchar>(i, j);
			histogram[value]++;
		}

	// 누적 등수(합) 계산 
	for (int i = 0; i < 256; i++) {
		sum += histogram[i];
		aug_histogram[i] = sum;
	}

	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++) {
			value = src.at<uchar>(i, j);
			dst.at<uchar>(i, j) = (Dm / area )*aug_histogram[value];
		}

	imshow("histogram equalization 결과", dst);
	waitKey(0);
}