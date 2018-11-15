#include <opencv2/highgui.hpp>

using namespace cv;

void main() {
	Mat src = imread("Mandrill_g.bmp", IMREAD_GRAYSCALE);
	Mat dst = Mat::zeros(src.size()*3, src.type());
	double const RATIO = 1.0/3.0;

	for(int i=0; i< dst.rows; i++)
		for( int j=0; j< dst.cols; j++) {
			int r = i / 3;
			int c = j / 3;
			double m1 = src.at<uchar>(r, c)  + RATIO * (src.at<uchar>(r, c+1) - src.at<uchar>(r, c));
			double m2 = src.at<uchar>(r +1, c) + RATIO * (src.at<uchar>(r +1, c+1) - src.at<uchar>(r +1, c));
			double p = m1 + RATIO * (m2 - m1);
			dst.at<uchar>(i, j) = p;
		}
	imshow("original", src);
	imshow("extension", dst);
	waitKey(0);
}