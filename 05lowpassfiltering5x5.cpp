#include <opencv2/highgui.hpp>
#include <string.h>
#include <math.h>

using namespace cv;

void main() {
	Mat src = imread("Mandrill.bmp", IMREAD_COLOR); 
	Mat dst = Mat::zeros(src.size(), src.type());
	double N = 5;

	double mask[3][3];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			mask[i][j] = 1 / (N*N);

	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++) {
			Vec3b augmented = (0,0,0);
			for (int mi = -1; mi <  N-1; mi++) 
				for (int mj = -1; mj < N - 1; mj++) {
					if(-1<i + mi && i+mi< src.rows && -1<j + mj && j + mj< src.cols)
						augmented = augmented + src.at<Vec3b>(i + mi, j + mj)*mask[mi + 1][mj + 1];
				
				}
			
			dst.at<Vec3b>(i, j) = augmented;
			
		}
		
		imshow("¿øº»", src);
		imshow("lowpassing", dst);
	
		waitKey(0);
}