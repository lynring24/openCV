#include <opencv2/highgui.hpp>
#include <iostream>
#include <list>
#include <math.h>

using namespace cv;
using namespace std;
typedef struct { int i; int j; } point;

void followBoundary(int i, int j);
point getNext(point temp);
bool isNewEdge(int i, int j);
point push_back(int i, int j);

list <point> edges;
point previous, mask;
Mat src;
int total = -1;

void main() {
	src = imread("circles.png");

	previous.i = 0, previous.j = -1;

	for (int i = 0; i< src.rows; i++) 
		for (int j = 0; j< src.cols; j++) 
			if ( src.at<Vec3b>(i, j) == cv::Vec3b(255, 255, 255)) {
				followBoundary(i, j); 
				edges.clear();
			}

	imshow("original", src);
	waitKey(0);
}

void followBoundary(int i, int j) {
	mask = previous;
	point edge = push_back(i, j);
	double diameter = 0, temp;

	do {
		//mask = previous;
		for (int cnt = 0; cnt < 9; cnt++) {

			mask = getNext(mask);
				if (src.at<Vec3b>(edge.i + mask.i, edge.j + mask.j) == cv::Vec3b(255, 255, 255)) {
					edge = push_back(edge.i + mask.i, edge.j + mask.j);
					//calculate diameter
					temp = pow(i - edge.i, 2.0)  + pow(j - edge.j, 2.0);
					if (temp > diameter)
						diameter = temp;

					previous = mask;
					break;
				}
				// mask = getNext(mask);
		}
	} while ( isNewEdge( edge.i + mask.i, edge.j + mask.j ));
	cout << "object number #" << (++total) << " diameter : " << sqrt(diameter) << endl;
}


point push_back(int i, int j) {
	point edge;
	edge.i = i;
	edge.j = j;
	edges.push_back(edge);
	src.at<Vec3b>(i, j) = cv::Vec3b(0, 0, 255);
	return edge;
}

bool isNewEdge(int i, int j) {
	bool isNew = true;
	list<point>::iterator iter;
	for (auto& iter : edges) {
		if (iter.i == i && iter.j == j) {
			isNew = false;
			break;
		}
	}
	return isNew;
}

point getNext(point temp) {
	if (temp.i == -1 && (temp.j == - 1 || temp.j == 0))
		temp.j = temp.j + 1;
	else if ((temp.i == -1 || temp.i == 0) && temp.j == 1)
		temp.i = temp.i + 1;
	else if (temp.i == 1 && (temp.j == 0 || temp.j == 1))
		temp.j = temp.j - 1;
	else if ((temp.i == 0 || temp.i == 1) && temp.j == -1)
		temp.i = temp.i - 1;
	return temp;
}