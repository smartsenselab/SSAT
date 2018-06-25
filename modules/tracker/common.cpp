#include "common.h"

using std::nth_element;

namespace cmt {

//TODO: Check for even/uneven number of elements
//The order of the elements of A is changed
float median(vector<float> & A)
{
    if (A.size() == 0)
    {
        return numeric_limits<float>::quiet_NaN();
    }

    nth_element(A.begin(), A.begin() + A.size()/2, A.end());

    return A[A.size()/2];
}

Point2f rotate(const Point2f v, const float angle)
{
    Point2f r;
    r.x = cos(angle) * v.x - sin(angle) * v.y;
    r.y = sin(angle) * v.x + cos(angle) * v.y;

    return r;
}

vector<float> getNextLineAndSplitIntoFloats(istream& str)
{
    vector<float>   result;
    string                line;
    getline(str,line);

    stringstream          lineStream(line);
    string                cell;
    while(getline(lineStream,cell,','))
    {
        result.push_back(atof(cell.c_str()));
    }
    return result;
}

string write_rotated_rect(RotatedRect rect)
{
    Point2f verts[4];
    rect.points(verts);
    stringstream coords;

    coords << rect.center.x << "," << rect.center.y << ",";
    coords << rect.size.width << "," << rect.size.height << ",";
    coords << rect.angle << ",";

    for (int i = 0; i < 4; i++)
    {
        coords << verts[i].x << "," << verts[i].y;
        if (i != 3) coords << ",";
    }

    return coords.str();
}

}
