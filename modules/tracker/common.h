#ifndef COMMON_H
#define COMMON_H

#include <limits>
#include <string>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/tracking.hpp>

using std::numeric_limits;
using std::string;
using std::vector;

using cv::Mat;
using cv::Point2f;
using cv::Rect;
using cv::RotatedRect;
using cv::Scalar;
using cv::Size2f;
using cv::VideoCapture;

using namespace std;

namespace cmt
{
float median(vector<float> & A);
Point2f rotate(const Point2f v, const float angle);
vector<float> getNextLineAndSplitIntoFloats(istream& str);
string write_rotated_rect(RotatedRect rect);

template<class T>
int sgn(T x)
{
    if (x >=0) return 1;
    else return -1;
}

}

#endif // COMMON_H
