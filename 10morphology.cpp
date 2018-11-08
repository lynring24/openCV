#include <opencv2/highgui.hpp>
#include <iostream>
#include <string.h>
#include <stack>

using namespace cv;
using namespace std;

void main() {
	Mat src, dst;
	src = imread("coin.bmp", IMREAD_GRAYSCALE);
	dst = Mat::zeros(src.size(), src.type());

	int N = 3; 
	Vec3b mask [3*3] = {90, 108, 108, 126, 144, 144, 162, 180, 180};
  //dilation
  for (int i = 0; i < src.rows; i++) 
		for (int j = 0; j < src.cols; j++) {
      int vote = 0;
			for (int mi = -N/2, m=0; mi < N - 1; mi++)
				for (int mj = -N / 2; mj < N - 1; mj++) {
					 if (mask[i+N/2][j+N/2] <= src.at<Vec3b>(i + mi, j + mj)) 
            vote ++;
				}
        
     if(vote) 
      dst.at<Vec3b>(i,j) = 255;
     else
      dst.at<Vec3b>(i,j) = 0;
		}  
  //erosion
	for (int i = 0; i < src.rows; i++) 
		for (int j = 0; j < src.cols; j++) {
      int vote =1;
			for (int mi = -N/2, m=0; mi < N - 1; mi++)
				for (int mj = -N / 2; mj < N - 1; mj++) {
					 if (mask[i+N/2][j+N/2] <= src.at<Vec3b>(i + mi, j + mj)) vote *=1;
           else vote*=0;
				}
     if(vote) 
      dst.at<Vec3b>(i,j) = 255;
     else
      dst.at<Vec3b>(i,j) = 0;
		}
    
    
    
	imshow(original", src);
	imshow("closing", dst);

	waitKey(0);
	
}

