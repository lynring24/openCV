#include <opencv2/highgui.hpp>
#include <math.h>

using namespace cv;

void main() {
	Mat src = imread("bird.bmp", IMREAD_GRAYSCALE);
	imshow("원본", src);


	int histogram[256] = { 0, };
	double posibility[256] = { 0, };
	int aug_histogram[256] = { 0, };
	int sum = 0;
	int value;
	double Dm = 255;
	double area = 0;

	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++) {
			int value = src.at<uchar>(i, j);
			histogram[value]++;
		}

	// 누적 등수(합) 계산 
	for (int i = 0; i < 256; i++) {
		sum += histogram[i];
		aug_histogram[i] = sum;
	}

	for (int i = 0; i < 256; i++)
		posibility[i] = (double)histogram[i] / src.rows * src.cols;

	double error[256];
	int threshold = 0;

	for (int K = 0; K < 256; K++) {
		error[K] = 0;
		double w0 = 0;
		for (int i = 0; i < K + 1; i++)
			w0 += posibility[i];
		double w1 = 0;
		for (int i = K + 1; i < 256; i++)
			w1 += posibility[i];

		if (w0 == 0 || w1 == 0)
			continue;

		double m0 = 0;
		for (int i = 0; i < K + 1; i++)
			m0 += (double)i*posibility[i] / w0;

		double m1 = 0;
		for (int i = K + 1; i < 256; i++)
			m1 += (double)i*posibility[i] / w1;

		double s0 = 0;
		for (int i = 0; i < K + 1; i++)
			s0 = s0 + pow(i - m0, 2)*posibility[i] / w0;

		double s1 = 0;
		for (int i = K + 1; i < 256; i++)
			s1 = s1 + pow(i - m1, 2)*posibility[i] / w1;

		error[K] = w0*s0 + w1*s1;

		if (threshold == 0)
			threshold = K;

	}

	for (int k = threshold; k < 256; k++)
		if (error[k] != 0 && error[threshold] >  error[k])
			threshold = k;

	Mat dst = Mat::zeros(src.size(), src.type());
	for (int i = 0; i<src.rows; i++)
		for (int j = 0; j < src.cols; j++) {
			if (src.at<uchar>(i, j) < threshold){
				value = src.at<uchar>(i, j);
				dst.at<uchar>(i, j) = (Dm / 2000)*aug_histogram[value];
			}
			else
				dst.at<uchar>(i, j) = 255;
		}

	imshow("local hdr result", dst);

	waitKey(0);
}