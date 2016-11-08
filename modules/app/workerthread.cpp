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

void WorkerThread::exportJSON(Core &_singleton, const QString &_jsonName){
    QJsonDocument out;
    QFile file;
    QJsonArray Array1, Array2, Array3, Array4, Array5, Array6;
    QJsonObject obj1, obj2, obj3, obj4, obj5, teste;

    map<string, BoundingBox> x;
    multimap<string, string> map1 = _singleton.attributes;
    multimap<string, string>::iterator i = map1.begin();
    vector<Frame>::iterator j = _singleton.frames.begin();

    int r=0;
    obj2["tracker"] = QString::fromStdString("CMT");
    obj2["version"] = QString::fromStdString("1.0.1");
    obj2["date"] =QDate::currentDate().toString();
    teste["Header"] = obj2;

    while( i != map1.end() ){
        obj1["Category"] = QString::fromStdString(i->first);
        obj1["label"] = QString::fromStdString(i->second);
        Array1.append(obj1);
        i++;
    }
    teste["Attributes"] = Array1;
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
    file.setFileName(_jsonName);
    file.open(QIODevice::WriteOnly);
    file.write(out.toJson());
}

void WorkerThread::importJSON(Core &_core, const QString &_path)
{
    _core.frameData.clear();
    _core.attributes.clear();

    QString val;
    QFile file;
    file.setFileName(_path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument json_Doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject json_Obj = json_Doc.object();

    FrameBasedData frameData;
    QJsonValue label, category, name, iniframe, endframe;
    std::string labelString, categoryString, nameString, iniframeString, endframeString;

    //HEADER
    QJsonValue json_Value = json_Obj.value(QString("Header"));
    QJsonObject item =  json_Value.toObject();
    QJsonValue tracker = item["tracker"];
    QJsonValue version = item["version"];
    QJsonValue date = item["date"];

    // ATTRIBUTES
    QJsonArray attributes = json_Obj["Attributes"].toArray();
    foreach (const QJsonValue & value, attributes) {
        QJsonObject obj = value.toObject();

        // CATEGORY
        category = obj.value("Category").toString();
        categoryString = category.toString().toUtf8().constData();

        // LABEL
        label = obj.value("label").toString();
        labelString = label.toString().toUtf8().constData();

        _core.attributes.insert(std::pair<string, string>(categoryString, labelString));
    }

    // FRAMETABLE
    int flag = 1;
    QJsonArray FrameTable = json_Obj["FrameTable"].toArray();
    foreach (const QJsonValue & value, FrameTable) {
        QJsonObject obj = value.toObject();

        // NAME
        name = obj.value("Name").toString();
        nameString = name.toString().toUtf8().constData();

        // CATEGORY
        category = obj.value("Category").toString();
        categoryString = category.toString().toUtf8().constData();

        // LABEL
        label = obj.value("label").toString();
        labelString = label.toString().toUtf8().constData();

        // INIFRAME
        iniframe = obj.value("IniFrame").toString();
        iniframeString = iniframe.toString().toUtf8().constData();

        // ENDFRAME
        endframe = obj.value("EndFrame").toString();
        endframeString = endframe.toString().toUtf8().constData();

        int init = std::stoi(iniframeString);
        int end = std::stoi(endframeString);

        frameData = FrameBasedData(init, end, categoryString, labelString, nameString);
        _core.frameData.push_back(frameData);
    }
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

