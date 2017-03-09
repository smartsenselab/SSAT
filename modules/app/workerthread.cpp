#include "workerthread.h"
#include "qdebug.h"

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
    QFile file;
    QJsonArray arrayJson1, arrayJson2;
    QJsonDocument output;
    QJsonObject object1, object2, object3, final;

    map<string, BoundingBox> x;
    multimap<string, string> map1 = _singleton.attributes;
    multimap<string, string>::iterator i = map1.begin();
    vector<Frame>::iterator j = _singleton.frames.begin();

    int r=0;
    object2["tracker"] = QString::fromStdString("CMT");
    object2["version"] = QString::fromStdString("1.0.1");
    object2["date"] =QDate::currentDate().toString();
    final["Header"] = object2;

    while(i != map1.end())
    {
        object1["Category"] = QString::fromStdString(i->first);
        object1["label"] = QString::fromStdString(i->second);
        arrayJson1.append(object1);
        i++;
    }

    final["Attributes"] = arrayJson1;
    for(auto iter:_singleton.frameData)
    {
        object3["Info"] = QString ::fromStdString(iter.getInfo());
        object3["Category"] = QString::fromStdString(iter.getCategory());
        object3["label"] = QString::fromStdString(iter.getLabel());
        object3["IniFrame"] = QString::fromStdString(std::to_string(iter.getInitialFrameId()));
        object3["EndFrame"] = QString::fromStdString(std::to_string(iter.getFinalFrameId()));
        arrayJson2.append(object3);
    }

    final["FrameTable"] = arrayJson2;
    output.setObject(final);
    file.setFileName(_jsonName);
    file.open(QIODevice::WriteOnly);
    file.write(output.toJson());
}

void WorkerThread::importJSON(Core &_singleton, QFrameBasedTableModel *_tableModel, const QString &_jsonName)
{
    _tableModel->clear();
    _singleton.attributes.clear();
    _singleton.frameData.clear();

    QString val;
    QFile file;
    file.setFileName(_jsonName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument json_Doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject json_Obj = json_Doc.object();

    FrameBasedData frameData;
    QJsonValue label, category, name, iniframe, endframe;
    std::string labelString, categoryString, nameString, iniframeString, endframeString;

    int percent = 0; // Percent = 100% of the ImportProgressBar

    // Header
    QJsonValue json_Value = json_Obj.value(QString("Header"));
    QJsonObject item =  json_Value.toObject();
    QJsonValue tracker = item["tracker"];
    QJsonValue version = item["version"];
    QJsonValue date = item["date"];
    percent += 3; // 3 values -> 1 for each ^

    // Attributes
    QJsonArray attributes = json_Obj["Attributes"].toArray();
    percent += attributes.size()*2; // 2 values per each attributes
    foreach (const QJsonValue & value, attributes) {
        QJsonObject obj = value.toObject();

        // Category
        category = obj.value("Category").toString();
        categoryString = category.toString().toUtf8().constData();

        // Label
        label = obj.value("label").toString();
        labelString = label.toString().toUtf8().constData();

        _singleton.attributes.insert(std::pair<string, string>(categoryString, labelString));
    }

    // FrameTable
    int flag = 1;
    QJsonArray FrameTable = json_Obj["FrameTable"].toArray();
    percent += FrameTable.size()*5; // 5 values per each FrameTable
    foreach (const QJsonValue & value, FrameTable) {
        QJsonObject obj = value.toObject();

        // Info
        name = obj.value("Info").toString();
        nameString = name.toString().toUtf8().constData();

        // Category
        category = obj.value("Category").toString();
        categoryString = category.toString().toUtf8().constData();

        // Label
        label = obj.value("label").toString();
        labelString = label.toString().toUtf8().constData();

        // IniFrame
        iniframe = obj.value("IniFrame").toString();
        iniframeString = iniframe.toString().toUtf8().constData();

        // EndFrame
        endframe = obj.value("EndFrame").toString();
        endframeString = endframe.toString().toUtf8().constData();

        int init = std::stoi(iniframeString);
        int end = std::stoi(endframeString);

        frameData = FrameBasedData(init, end, categoryString, labelString, nameString);
        _tableModel->insertRow(frameData);
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

void WorkerThread::insertFrameBasedSegment(Core &_singleton, const FrameBasedData &_data)
{
    _singleton.frameData.push_back(_data);
}

void WorkerThread::alterFrameBasedSegment(Core &_singleton, const FrameBasedData &_data, const int _index)
{
    _singleton.frameData[static_cast<unsigned long>(_index)] = _data;
}

