#include "workerthread.h"

WorkerThread::WorkerThread()
{
    this->playing = false;
}

WorkerThread::~WorkerThread()
{
    this->clearVideo();
}

Mat WorkerThread::getFrame()
{
    Mat frame;
    this->video >> frame;
    return frame;
}

Mat WorkerThread::getFrame(double _frameId)
{
    Mat frame;
    this->video.set(CV_CAP_PROP_POS_FRAMES, _frameId);
    this->video >> frame;
    return frame;
}

double WorkerThread::getFrameId()
{
    return this->video.get(CV_CAP_PROP_POS_FRAMES);
}

double WorkerThread::getTotalFrames()
{
    return this->video.get(CV_CAP_PROP_FRAME_COUNT);
}

double WorkerThread::getVideoFPS()
{
    return this->video.get(CV_CAP_PROP_FPS);
}

bool WorkerThread::isPlaying()
{
    return this->playing;
}

void WorkerThread::isPlaying(bool _condition)
{
    this->playing = _condition;
}

void WorkerThread::clearVideo()
{
    this->video.release();
}

void WorkerThread::loadVideo(QString _path)
{
    this->video.open(_path.toStdString());
}

void WorkerThread::slot_exportJson(Core &_singleton,QString jsonName){
QJsonObject obj;
QFile file;
multimap<string, string> map1 = _singleton.attributes;
multimap<string, string>::iterator i = map1.begin();
vector<Frame>::iterator j = _singleton.frames.begin();
map<string, BoundingBox> x;
QJsonObject teste;
QJsonDocument out;
QJsonArray Array;
QJsonArray Array2;
QJsonArray Array3;
QJsonArray Array4;
QJsonArray Array5;
QJsonArray Array6;
QJsonObject obj2;
QJsonObject obj3;
QJsonObject obj4;
QJsonObject obj5;
int r=0;
obj2["tracker"] = QString::fromStdString("CMT");
obj2["version"] = QString::fromStdString("1.0.1");
obj2["date"] =QDate::currentDate().toString();
teste["Header"] = obj2;

while( i != map1.end() ){
    obj["Category"] = QString::fromStdString(i->first);
    obj["label"] = QString::fromStdString(i->second);
    Array.append(obj);
    i++;
}
teste["Attributes"] = Array;
int frame_num = 0;
while(j!=_singleton.frames.end()){
   string a = std::to_string(j->getId());
   string c = j->getName();
   vector<string> frame_obj = j->getAttributes("Object_recognition");
   vector<string> person = j->getAttributes("Person_identification");
   for(auto elemen:frame_obj){
       Array5.append(QString::fromStdString(elemen));
   }
   for(auto elemen: person){
       Array6.append(QString::fromStdString(elemen));
   }
   obj5["Object_regognition"] = Array5;
   obj5["Person_identification"] = Array6;
   obj3["Attributes"] = obj5;
   obj3["ID"] = QString::fromStdString(a);
   obj3["Name"] = QString::fromStdString(c);
   obj3["numero_frame"] = frame_num;
   if(j->getBoxes().empty()==false){
    x = j->getBoxes();
    for (auto elemen:x){
        obj4["cat_id"] = QString::fromStdString(elemen.first);
        obj4["X"] = elemen.second.getX();
        obj4["Y"] = elemen.second.getY();
        obj4["W"] = elemen.second.getW();
        obj4["H"] = elemen.second.getH();
        Array3.append(obj4);
    }
   }
   obj3["boxes"] = Array3;
   for(auto elemen:j->getComments()){
    Array4.append(QString::fromStdString(elemen));
   }
   obj3["comment"] = Array4;
   for(int j=0;j<4;j++){
   Array3.removeFirst();
   }
   Array2.append(obj3);
   j++;
   frame_num++;
}
teste["Frames"] = Array2;
out.setObject(teste);
file.setFileName(jsonName);
file.open(QIODevice::WriteOnly);
file.write(out.toJson());
}

void WorkerThread::importJSON(Core &_core, const QString &_path)
{
    //Breno e Danilo: adicioanar implementação aqui
}

QImage WorkerThread::matToQimage(const Mat &_frameId)
{
    if (_frameId.type() == CV_8UC3)
    {
        const uchar *qImageBuffer = const_cast<uchar*>(_frameId.data);
        QImage img(qImageBuffer, _frameId.cols, _frameId.rows, static_cast<int>(_frameId.step), QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    else
    {
        qErrnoWarning("ERROR: Mat could not be converted to QImage.");
        return QImage();
    }
}

void WorkerThread::allotFrameBasedSegment(Core &_singleton, const FrameBasedData &_data)
{
    for(int frameId = _data.getInitialFrameId(); frameId <= _data.getFinalFrameId(); frameId++)
    {
        unsigned long longFrameId = static_cast<unsigned long>(frameId);
        _singleton.frames[longFrameId].setName(_data.getName());
        _singleton.frames[longFrameId].addAttributes("_data.getCategory()", "_data.getLabel()");
//        _singleton.frames[longFrameId].addAttributes(_data.getCategory(), _data.getLabel());
    }
}
