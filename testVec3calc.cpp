#include <opencv2/highgui.hpp>
#include<iostream>
#include <string.h>
#include <math.h>

using namespace cv;
using namespace std;

void main() {
	Mat src = imread("Mandrill.bmp", IMREAD_COLOR); 
	Mat dst = Mat::zeros(src.size(), src.type());
	double N = 5;

	double mask[3][3];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) 
			mask[i][j] = 1 / (N*N);
	
	cout << src.at<Vec3b>(40, 40)<< "  "<<src.at<Vec3b>(40, 40) * 1 / (N*N) << endl;

	waitKey(0);
}