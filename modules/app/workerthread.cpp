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

void WorkerThread::exportJSON(Core &_singleton, const QString &_jsonName)
{
    QFile file;
    QJsonArray attributeArray, boxArray, frameArray, frameDataArray;
    QJsonDocument output;
    QJsonObject attributesObject, boxObject, headerObject, frameDataObject, frameObject, final;

    multimap<string, string>::iterator attribute_it;
    vector<FrameBasedData>::iterator frameData_it;
    vector<Frame>::iterator frame_it;
    map<unsigned int, BoundingBox>::iterator box_it;

    // Exporting Header
    headerObject["Tracker"] = QString::fromStdString("CMT");
    headerObject["Version"] = QString::fromStdString("1.0.1");
    headerObject["Date"] = QDate::currentDate().toString();
    final["Header"] = headerObject;

    // Exporting Attributes
    for(attribute_it = _singleton.attributes.begin(); attribute_it != _singleton.attributes.end(); attribute_it++)
    {
        attributesObject["Category"] = QString::fromStdString(attribute_it->first);
        attributesObject["Label"] = QString::fromStdString(attribute_it->second);
        attributeArray.append(attributesObject);
    }
    final["Attributes"] = attributeArray;

    // Exporting Frame annotation
    for(frameData_it = _singleton.frameData.begin(); frameData_it != _singleton.frameData.end(); frameData_it++)
    {
        frameDataObject["Info"] = QString::fromStdString(frameData_it->getInfo());
        frameDataObject["Category"] = QString::fromStdString(frameData_it->getCategory());
        frameDataObject["Label"] = QString::fromStdString(frameData_it->getLabel());
        frameDataObject["IniFrame"] = QString::fromStdString(std::to_string(frameData_it->getInitialFrameId()));
        frameDataObject["EndFrame"] = QString::fromStdString(std::to_string(frameData_it->getFinalFrameId()));
        frameDataArray.append(frameDataObject);
    }
    final["FrameTable"] = frameDataArray;

    // Exporting BoundingBox annotation
    map<unsigned int, BoundingBox> boxes;
    for(frame_it = _singleton.frames.begin(); frame_it != _singleton.frames.end(); frame_it++)
    {
        boxes = frame_it->getBoxes();
        for(box_it = boxes.begin(); box_it != boxes.end(); box_it++)
        {
            boxObject[""] =
        }

    }
    final["Frames"] = frameDataArray;


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

    // Load file
    QFile file;
    QString streamFile;
    file.setFileName(_jsonName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    streamFile = file.readAll();
    file.close();

    QJsonDocument json_Doc = QJsonDocument::fromJson(streamFile.toUtf8());
    QJsonObject json_Obj = json_Doc.object();

    FrameBasedData frameData;
    QJsonValue label, category, name, iniframe, endframe;
    std::string labelString, categoryString, nameString, iniframeString, endframeString;

    // Importing Header
    QJsonValue json_Value = json_Obj.value(QString("Header"));
    QJsonObject item =  json_Value.toObject();
    QJsonValue tracker = item["Tracker"];
    QJsonValue version = item["Version"];
    QJsonValue date = item["Date"];

    // Importing Attributes
    QJsonArray attributes = json_Obj["Attributes"].toArray();
    foreach (const QJsonValue & value, attributes) {
        QJsonObject obj = value.toObject();

        // Category
        category = obj.value("Category").toString();
        categoryString = category.toString().toUtf8().constData();

        // Label
        label = obj.value("Label").toString();
        labelString = label.toString().toUtf8().constData();

        _singleton.attributes.insert(std::pair<string, string>(categoryString, labelString));
    }

    // FrameTable
    QJsonArray FrameTable = json_Obj["FrameTable"].toArray();
    foreach (const QJsonValue & value, FrameTable) {
        QJsonObject obj = value.toObject();

        // Info
        name = obj.value("Info").toString();
        nameString = name.toString().toUtf8().constData();

        // Category
        category = obj.value("Category").toString();
        categoryString = category.toString().toUtf8().constData();

        // Label
        label = obj.value("Label").toString();
        labelString = label.toString().toUtf8().constData();

        // IniFrame
        iniframe = obj.value("IniFrame").toString();
        iniframeString = iniframe.toString().toUtf8().constData();
        int init = std::stoi(iniframeString);

        // EndFrame
        endframe = obj.value("EndFrame").toString();
        endframeString = endframe.toString().toUtf8().constData();
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

