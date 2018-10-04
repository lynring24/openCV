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
	Vec3b mask [3*3];
	for (int i = 0; i < src.rows; i++) 
		for (int j = 0; j < src.cols; j++) {

			//calc mask
			for (int mi = -N/2, m=0; mi < N - 1; mi++)
				for (int mj = -N / 2; mj < N - 1; mj++) {
					mask[m++] = src.at<Vec3b>(i + mi, j + mj);
				}

			//sort mask
			int mi;
			for (mi = 0; mi < N*N; mi++) {
				for(int mj=mi+1;mj<N*N;mj++){
					double norm_current = cv::norm(mask[mi], CV_L2);
					if (norm_current == 0.0) break;
					double norm_next = cv::norm(mask[mj], CV_L2);
					if (norm_current > norm_next) {
						Vec3b temp = mask[mi];
						mask[mi] = mask[mj];
						mask[mj] = temp;
					}
				}
			}

			dst.at<Vec3b>(i,j) = mask[mi/2];
			
		}
	imshow("¿øº»", src);
	imshow("medianfiltering", dst);

	waitKey(0);
	
}
