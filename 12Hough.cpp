#include <opencv2/highgui.hpp>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace cv;
using namespace std;

int width = 100;
int height = 256 * 2 + 1;
int hough[100][256 * 2 + 1] = { 0, };
double theta, rho;

double maxr = 0, minr = 0;

double getHoughTransfrom(int x, int y, int angle);
void transformHoughAt(int x, int y);
Point getMaxHough();

void main() {
	Mat src = imread("edge.bmp", IMREAD_COLOR);

	for (int x = 0; x < src.rows; x++)
		for (int y = 0; y < src.cols; y++)
			transformHoughAt(x , y);
	
	Point max = getMaxHough();
	//cout << maxr << "		" << minr << endl;
	//get max degree from the max point 
	theta = M_PI / (double) width * max.x;
	// max.y = max.y - 256;
	//from dst image, check if the value of transfrom pass by the point 
	
	Mat dst = Mat::zeros(src.size(), src.type());
	for (int x = 0; x < src.rows; x++)
		for (int y = 0; y < src.cols; y++)
			dst.at<Vec3b>(x, y) = src.at<Vec3b>(x, y);

	for (int x = 0, y= 0; x < 256; x ++) {
		y = - cos(theta) / sin(theta) * x  + max.y / sin(theta); 
		if (y > -1 && y < 256)
			dst.at<Vec3b>(x, y)[2] = 255;
	}

	imshow("origin", src);
	imshow("Hough", dst);
	waitKey(0);
}
double getHoughTransfrom(int x, int y, int angle) {
	theta = (double) angle * M_PI / (double) width;
	rho = double(x)*cos(theta) + double(y)*sin(theta);
	if (rho > maxr) maxr = rho;
	if (rho < minr) minr = rho;
	return rho;
}

void transformHoughAt(int x, int y) {
	for (int angle = 0; angle < width; angle++) {
		y = getHoughTransfrom(x, y, angle);
		hough[angle][y]++;
	}
}

Point getMaxHough() {
	int current = 0;
	Point max = (0, 0);
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			if (current < hough[x][y]) {
				current = hough[x][y];
				max.x = x;
				max.y = y;
				cout << " ( " << max.x << ", " << max.y << ") " << endl;
			}
	return max;
}

