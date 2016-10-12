#include "cmthread.h"

namespace cmt
{

CMThread::CMThread(VideoCapture _video, Rect _rectangle, string _name, int _frame)
{
    this->cmtSetup (_video, _rectangle, _frame);
    this->name = _name;
}

int CMThread::display(Mat image, CMT &cmt)
{
    for(size_t i = 0; i < cmt.points_active.size(); i++)
    {
        circle(image, cmt.points_active[i], 2, Scalar(255,0,0));
    }

    Point2f vertices[4];
    cmt.bb_rot.points(vertices);
    for (int i = 0; i < 4; i++)
    {
        line(image, vertices[i], vertices[(i+1)%4], Scalar(255,0,0));
    }

    imshow("CMT", image);

    return cv::waitKey(1);
}

void CMThread::run()
{
    ofstream outfile;
    outfile.open(this->name);

    int current = this->frame;
    Mat grayInitialView, initialView;
    Point2f vertices[4];

    this->video.set(CV_CAP_PROP_POS_FRAMES, this->frame);
    this->video >> initialView;

    if(initialView.channels() > 1)
    {
        cv::cvtColor(initialView, grayInitialView, CV_BGR2GRAY);
    }
    else
    {
        grayInitialView = initialView;
    }

    this->cmt.initialize(grayInitialView, this->rectangle);

    while(true)
    {
        Mat currentView, grayCurrentView;

        current++;
        this->video >> currentView;

        if(currentView.empty())
        {
            break;
        }

        if(currentView.channels() > 1)
        {
            cv::cvtColor(currentView, grayCurrentView, CV_BGR2GRAY);
        }
        else
        {
            grayCurrentView = currentView;
        }

        this->cmt.processFrame(grayCurrentView);
//        this->display(currentView, this->cmt);


        cmt.bb_rot.points(vertices);
        outfile << current << ": ";
        for (int i = 0; i < 4; i++)
        {
            outfile << vertices[i] << " ";
        }
        outfile << endl;
    }

    outfile.close();
}

void CMThread::cmtSetup (cv::VideoCapture _video, cv::Rect _rectangle, int _frame)
{
    this->frame = _frame;
    this->rectangle = _rectangle;
    this->video = _video;
}

}
