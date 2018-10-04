#include <opencv2/highgui.hpp>
#include <iostream>
#include <string.h>
#include <stack>

using namespace cv;
using namespace std;

void main() {
	Mat src, dst;
	src = imread("pepper_noise.bmp", IMREAD_COLOR);
	dst = Mat::zeros(src.size(), src.type());

	int N = 3;
	Vec3b mask [9];

	imshow("원본", src);
	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++) {

			//calc mask
		
			for (int mi = -N / 2; mi < N - 1; mi++)
				for (int mj = -N / 2; mj < N - 1; mj++) {
					mask[N*(mi + 1) + (mj + 1)] = src.at<Vec3b>(i, j);
				}

			//sort mask
			for (int mi = 0; mi < N; mi++) {
				for (int mj = 0; mj < N; mj++) {
					double norm_current = cv::norm(mask[mi*N + mj], CV_L2);
					double norm_next = cv::norm(mask[mi*N + mj + 1], CV_L2);
					if (norm_current > norm_next)
						swap(mask[mi*N + mj], mask[mi*N + mj + 1]);
				}
			}
			//get median and store to dst
			dst.at<Vec3b>(i, j) = mask[4];
			

		}
	imshow("원본", src);
	imshow("median", dst);

	waitKey(0);

}

void swap(char& a, char& b) {
	char temp;
	temp = a;
	a = b;
	b = a;
}