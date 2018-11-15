#include <opencv2/highgui.hpp>
using namespace cv;

void main() {
	Mat src = imread("Mandrill_g.bmp", IMREAD_GRAYSCALE);
	Mat dst = Mat::zeros(src.size(), src.type());
	double Ep = 0.0;
	int Eg[256][256] = {0, };
	int c[2][3] = { 0, 0, 7, 3, 5, 1 };
	double T = -1;
	int threshold = 120;
	
	for (int m = 0; m < src.rows; m++)
		for (int n = 0; n < src.cols; n++) {
			//calculate the total propogated error at (m,n) due to prior assignments 
			Ep = 0;
			for (int i = 0; i < 2; i++) 
				for (int j = -1; j < 2; j++) 
					if(-1 < m - i && -1 < n + j && -1 < 1 - j)
							Ep += Eg[m - i][n + j] * c[i][1 - j];
			Ep = Ep / 16.0;

			T = src.at<uchar>(m, n) + Ep;
			if (T > threshold) {
				dst.at<uchar>(m, n) = 255;
				Eg[m][n] = T - 2 * threshold;
			}
			else {
				dst.at<uchar>(m, n) = 0;
				Eg[m][n] = threshold;
			}
		}
	imshow("original image", src);
	imshow("dithering output", dst);
	waitKey(0);
}