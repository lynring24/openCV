#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define PI 3.14159265
#define BYTE unsigned char 


int main(int argc, char** argv) {
	Mat src = imread("edge.bmp", IMREAD_COLOR);
	Mat dst = Mat::zeros(src.size(), src.type());


	int cm[256 * 2 + 1][100];

	for (int i = 0; i<256 * 2 + 1; i++)
		for (int j = 0; j<100; j++)
			cm[i][j] = 0;


	double rho, theta;
	int r;

	for (int i = 0; i<256; i++)
	{
		for (int j = 0; j<256; j++)
		{
			if (src.at<Vec3b>(i, j)[0] == 255)
			{
				for (int t = 0; t<100; t++)
				{
					theta = PI / 100 * t;
					rho = double(j)*cos(theta) + double(i)*sin(theta);
					r = 256 - int(rho + 0.5)  ;
					cm[r][t] = cm[r][t] + 1;
				}
			}
		}
	}

	int max_num = 0;
	int r_loc;
	int t_loc;
	for (int i = 0; i<256 * 2 + 1; i++)
		for (int j = 0; j<100; j++)
			if (cm[i][j]>max_num)
			{
				max_num = cm[i][j];
				r_loc = i;
				t_loc = j;
			}

	// cout  << r_loc << " " << t_loc <<  endl;
	theta = PI / 100 * t_loc;
	r = 256 - int(rho + 0.5);
	rho = 256 - r_loc;


	for (int i = 0; i<256; i++)
	{
		for (int j = 0; j<256; j++)
		{
			for (int c = 0; c<3; c++)
			{
				dst.at<Vec3b>(i, j)[c] = src.at<Vec3b>(i, j)[c];
			}
		}
	}
	int y;
	for (int j = 0; j<256; j++)
	{
		y = -cos(theta) / sin(theta)*j + rho / sin(theta);
		int temp = y + 0.5;
		if (int(temp) > 0 && int(temp) < 256) {
			dst.at<Vec3b>(int(temp), j)[2] = 255;
		}
	}

	namedWindow("Image");
	imshow("Image", src);

	namedWindow("Result");
	imshow("Result", dst);
	imwrite("result.bmp", dst);
	waitKey(0);

	return 0;
}