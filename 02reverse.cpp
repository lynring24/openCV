#include <opencv2/highgui.hpp>

using namespace cv;

void main() {
	Mat src = imread("Mandrill.bmp", IMREAD_COLOR);
	Mat dst = Mat::zeros(src.size(), src.type());
	Mat dst2 = Mat::zeros(src.size(), src.type());
	Mat channel[3], channelOut[3];
	
	split(src, channel);
	for(int i=0 ; i<3; i++)
		bitwise_not(channel[i], channelOut[i]);
	merge(channelOut, 3, dst2);

	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++)
			for (int c = 0; c < 3; c++) {
				dst.at<Vec3b>(i, j)[c] = 255 - src.at<Vec3b>(i, j)[c];
				
			}
	imshow("역상1", dst);
	imshow("역상2", dst2);
	waitKey(0);

	
}