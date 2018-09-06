#include "qworkerthread.h"
#include "qdebug.h"

QWorkerThread::QWorkerThread()
{
    this->playing = false;
}

QWorkerThread::~QWorkerThread()
{
    this->clearVideo();
}

Mat QWorkerThread::getFrame()
{
    Mat frame;
    this->video >> frame;
    return frame;
}

Mat QWorkerThread::getFrame(double _frameId)
{
    Mat frame;
    this->video.set(CV_CAP_PROP_POS_FRAMES, _frameId);
    this->video >> frame;
    return frame;
}

double QWorkerThread::getFrameId()
{
    return this->video.get(CV_CAP_PROP_POS_FRAMES);
}

double QWorkerThread::getTotalFrames()
{
    return this->video.get(CV_CAP_PROP_FRAME_COUNT);
}

double QWorkerThread::getVideoFPS()
{
    return this->video.get(CV_CAP_PROP_FPS);
}

bool QWorkerThread::isPlaying()
{
    return this->playing;
}

void QWorkerThread::isPlaying(bool _condition)
{
    this->playing = _condition;
}

void QWorkerThread::clearVideo()
{
    this->video.release();
}

void QWorkerThread::loadVideo(QString _path)
{
    this->video.open(_path.toStdString());
}

void QWorkerThread::exportJSON(Core &_singleton, const QString &_jsonName)
{
    QFile file;
    QJsonArray attributeArrays, frameArray, frameDataArray;
    QJsonDocument output;
    QJsonObject attributesObject, headerObject, frameDataObject, frameObject, settingsObject, final;

    vector< vector<string> >::iterator attribute_out;
    vector<string>::iterator attribute_in;
    multimap<string, string>::iterator attribute_it;
    vector<FrameBasedData>::iterator frameData_it;
    vector<Frame>::iterator frame_it;
    map<unsigned int, BoundingBox>::iterator box_it;

    // Exporting Header
    headerObject["Date"] = QDate::currentDate().toString();
    headerObject["Tracker"] = QString::fromStdString("CMT");
    headerObject["Version"] = QString::fromStdString("1.0.2");
    final["Header"] = headerObject;

    // Exporting Settings
    settingsObject["currentSeparator"] = QString::fromStdString(_singleton.setup.getCurrentSeparator());
    settingsObject["latestCategory"] = QString::fromStdString(_singleton.setup.getLatestCategory());
    settingsObject["latestLabel"] = QString::fromStdString(_singleton.setup.getLatestLabel());
    settingsObject["frameSkip"] = QString::fromStdString(std::to_string(_singleton.setup.getFrameSkip()));
    settingsObject["largestId"] = QString::fromStdString(std::to_string(_singleton.setup.getLargestId()));
    settingsObject["latestId"] = QString::fromStdString(std::to_string(_singleton.setup.getLatestId()));
    settingsObject["latestKey"] = QString::fromStdString(std::to_string(_singleton.setup.getLatestKey()));
    final["Settings"] = settingsObject;

    // Exporting Attributes
    vector< vector<string> > attributesPath = _singleton.labelTree->getAttributesPath();
    for(attribute_out = attributesPath.begin(); attribute_out != attributesPath.end(); attribute_out++)
    {
        QJsonArray attributeArray;
        for(attribute_in = attribute_out->begin(); attribute_in != attribute_out->end(); attribute_in++)
        {
            QString temp = QString::fromStdString(*attribute_in);
            attributeArray.append(temp);
        }
        attributeArrays.append(attributeArray);
    }
    final["Attributes"] = attributeArrays;

    // Exporting Frame annotation
    for(frameData_it = _singleton.frameData.begin(); frameData_it != _singleton.frameData.end(); frameData_it++)
    {
        frameDataObject["Category"] = QString::fromStdString(frameData_it->getCategory());
        frameDataObject["Id"] = QString::fromStdString(std::to_string(frameData_it->getId()));
        frameDataObject["Info"] = QString::fromStdString(frameData_it->getInfo());
        frameDataObject["Label"] = QString::fromStdString(frameData_it->getLabel());
        frameDataObject["Name"] = QString::fromStdString(frameData_it->getName());
        frameDataObject["IniFrame"] = QString::fromStdString(std::to_string(frameData_it->getInitialFrameId()));
        frameDataObject["EndFrame"] = QString::fromStdString(std::to_string(frameData_it->getFinalFrameId()));
        frameDataArray.append(frameDataObject);
    }
    final["FrameBased"] = frameDataArray;

    // Exporting BoundingBox annotation
    map<unsigned int, BoundingBox> boxes;
    for(frame_it = _singleton.frames.begin(); frame_it != _singleton.frames.end(); frame_it++)
    {
        QJsonArray boxArray;
        QJsonObject boxObject;

        frameObject["Category"] = QString::fromStdString(frame_it->getCategory());
        frameObject["Id"] = QString::fromStdString(std::to_string(frame_it->getId()));
        frameObject["Info"] = QString::fromStdString(frame_it->getInfo());
        frameObject["Label"] = QString::fromStdString(frame_it->getLabel());
        frameObject["Name"] = QString::fromStdString(frame_it->getName());

        boxes = frame_it->getBoxes();
        for(box_it = boxes.begin(); box_it != boxes.end(); box_it++)
        {
            boxObject["Category"] = QString::fromStdString(box_it->second.getCategory());
            boxObject["Id"] = QString::fromStdString(std::to_string(box_it->second.getId()));
            boxObject["Info"] = QString::fromStdString(box_it->second.getInfo());
            boxObject["Label"] = QString::fromStdString(box_it->second.getLabel());
            boxObject["Name"] = QString::fromStdString(box_it->second.getName());

            boxObject["X"] = QString::fromStdString(std::to_string(box_it->second.getX()));
            boxObject["Y"] = QString::fromStdString(std::to_string(box_it->second.getY()));
            boxObject["W"] = QString::fromStdString(std::to_string(box_it->second.getW()));
            boxObject["H"] = QString::fromStdString(std::to_string(box_it->second.getH()));
            boxArray.append(boxObject);
        }
        frameObject["Boxes"] = boxArray;
        frameArray.append(frameObject);
    }
    final["Frames"] = frameArray;

    output.setObject(final);
    file.setFileName(_jsonName);
    file.open(QIODevice::WriteOnly);
    file.write(output.toJson());
}

void QWorkerThread::importJSON(Core &_singleton, QFrameBasedTableModel *_tableModel, const QString &_jsonName)
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
    QJsonValue category, id, info, label, name, iniFrame, endFrame;

    std::string categoryStr, idStr, infoStr, labelStr, nameStr, iniFrameStr, endFrameStr;

    // Importing Header
    QJsonValue json_Value = json_Obj.value(QString("Header"));
    QJsonObject item =  json_Value.toObject();
    QJsonValue tracker = item["Tracker"];
    QJsonValue version = item["Version"];
    QJsonValue date = item["Date"];

    // Importing Attributes
    QJsonArray attributes = json_Obj["Attributes"].toArray();
    foreach (const QJsonValue & value, attributes)
    {
        QJsonObject obj = value.toObject();

        // Category
        category = obj.value("Category").toString();
        categoryStr = category.toString().toUtf8().constData();

        // Label
        label = obj.value("Label").toString();
        labelStr = label.toString().toUtf8().constData();

        _singleton.attributes.insert(std::pair<string, string>(categoryStr, labelStr));
    }

    // Importing Frame annotation
    QJsonArray FrameTable = json_Obj["FrameBased"].toArray();
    foreach (const QJsonValue & value, FrameTable)
    {
        QJsonObject obj = value.toObject();

        // Category
        category = obj.value("Category").toString();
        categoryStr = category.toString().toUtf8().constData();

        // Id
        id = obj.value("Id").toString();
        idStr = id.toString().toUtf8().constData();
        int idInt = std::stoi(idStr);

        // Info
        info = obj.value("Info").toString();
        infoStr = info.toString().toUtf8().constData();

        // Label
        label = obj.value("Label").toString();
        labelStr = label.toString().toUtf8().constData();

        // Name
        name = obj.value("Name").toString();
        nameStr = name.toString().toUtf8().constData();

        // IniFrame
        iniFrame = obj.value("IniFrame").toString();
        iniFrameStr = iniFrame.toString().toUtf8().constData();
        int initInt = std::stoi(iniFrameStr);

        // EndFrame
        endFrame = obj.value("EndFrame").toString();
        endFrameStr = endFrame.toString().toUtf8().constData();
        int endInt = std::stoi(endFrameStr);

        FrameBasedData tempFrameData(idInt, categoryStr, infoStr, labelStr, nameStr, initInt, endInt);
        _tableModel->insertRow(tempFrameData);
    }

    // Importing BoundingBox annotation
    QJsonArray Frames = json_Obj["Frames"].toArray();
    foreach (const QJsonValue & frameValue, Frames)
    {
        QJsonObject frameObj = frameValue.toObject();

        // Id
        id = frameObj.value("Id").toString();
        idStr = id.toString().toUtf8().constData();
        int idInt = std::stoi(idStr);

        if (idInt < _singleton.frames.size())
        {
            // Category
            category = frameObj.value("Category").toString();
            categoryStr = category.toString().toUtf8().constData();

            // Info
            info = frameObj.value("Info").toString();
            infoStr = info.toString().toUtf8().constData();

            // Label
            label = frameObj.value("Label").toString();
            labelStr = label.toString().toUtf8().constData();

            // Name
            name = frameObj.value("Name").toString();
            nameStr = name.toString().toUtf8().constData();

            Frame tempFrame(idInt, categoryStr, infoStr, labelStr, nameStr);
            QJsonValue bCategory, bId, bInfo, bLabel, bName, bX, bY, bW, bH;
            std::string bCategoryStr, bIdStr, bInfoStr, bLabelStr, bNameStr, bXstr, bYstr, bWstr, bHstr;

            QJsonArray Boxes = frameObj["Boxes"].toArray();
            foreach (const QJsonValue & boxValue, Boxes)
            {
                QJsonObject boxObj = boxValue.toObject();

                // Category
                bCategory = boxObj.value("Category").toString();
                bCategoryStr = bCategory.toString().toUtf8().constData();

                // Id
                bId = boxObj.value("Id").toString();
                bIdStr = bId.toString().toUtf8().constData();
                int bIdInt = std::stoi(bIdStr);

                // Info
                bInfo = boxObj.value("Info").toString();
                bInfoStr = bInfo.toString().toUtf8().constData();

                // Label
                bLabel = boxObj.value("Label").toString();
                bLabelStr = bLabel.toString().toUtf8().constData();

                // Name
                bName = boxObj.value("Name").toString();
                bNameStr = bName.toString().toUtf8().constData();

                // X coordinate
                bX = boxObj.value("X").toString();
                bXstr = bX.toString().toUtf8().constData();
                int bXint = std::stoi(bXstr);

                // Y coordinate
                bY = boxObj.value("Y").toString();
                bYstr = bY.toString().toUtf8().constData();
                int bYint = std::stoi(bYstr);

                // W coordinate
                bW = boxObj.value("W").toString();
                bWstr = bW.toString().toUtf8().constData();
                int bWint = std::stoi(bWstr);

                // H coordinate
                bH = boxObj.value("H").toString();
                bHstr = bH.toString().toUtf8().constData();
                int bHint = std::stoi(bHstr);

                BoundingBox tempBox(bIdInt, bCategoryStr, bInfoStr, bLabelStr, bNameStr, bXint, bYint, bWint, bHint, true);
                tempFrame.addBox(tempBox);

                _singleton.setup.tracklets.insert(bIdInt);
            }

            _singleton.frames[idInt] = tempFrame;
        }
        else
        {
            std::cerr << "JSON frame id " << idInt << " is greater than video length.";
        }
    }
}

QImage QWorkerThread::matToQimage(const Mat &_frameId)
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

void QWorkerThread::insertFrameBasedSegment(Core &_singleton, const FrameBasedData &_data)
{
    _singleton.frameData.push_back(_data);
}

void QWorkerThread::alterFrameBasedSegment(Core &_singleton, const FrameBasedData &_data, const int _index)
{
    _singleton.frameData[static_cast<unsigned long>(_index)] = _data;
}

void QWorkerThread::exponentialForget(Core &_singleton, BoundingBox _focusBox, const unsigned int _frameId, const unsigned int _numFrames)
{
    double holder = 1.0;
    double step = 1.0 / _numFrames;
    int newX, newY, newW, newH;

    // Moving backwards
    holder = 1.0;
    for(unsigned int frameIndex = _frameId;
        (frameIndex > 0) && (frameIndex >= _frameId - _numFrames);
        frameIndex--)
    {
        BoundingBox bbox = _singleton.frames[frameIndex].getBoxById(_focusBox.getId());
        if (bbox.isValid() && (bbox.getModify()))
        {
            newX = (holder * _focusBox.getX()) + ((1 - holder) * bbox.getX());
            newY = (holder * _focusBox.getY()) + ((1 - holder) * bbox.getY());
            newW = (holder * _focusBox.getW()) + ((1 - holder) * bbox.getW());
            newH = (holder * _focusBox.getH()) + ((1 - holder) * bbox.getH());

            _singleton.frames[frameIndex].setBox(bbox.getKey(), newX, newY, newW, newH);
            holder -= step;
        }
        else break;
    }

    // Moving forward
    holder = 1.0;
    for(unsigned int frameIndex = _frameId;
        (frameIndex < _singleton.frames.size()) && (frameIndex <= _frameId + _numFrames);
        frameIndex++)
    {
        BoundingBox bbox = _singleton.frames[frameIndex].getBoxById(_focusBox.getId());
        if (bbox.isValid() && (bbox.getModify()))
        {
            newX = (holder * _focusBox.getX()) + ((1 - holder) * bbox.getX());
            newY = (holder * _focusBox.getY()) + ((1 - holder) * bbox.getY());
            newW = (holder * _focusBox.getW()) + ((1 - holder) * bbox.getW());
            newH = (holder * _focusBox.getH()) + ((1 - holder) * bbox.getH());

            _singleton.frames[frameIndex].setBox(bbox.getKey(), newX, newY, newW, newH);
            holder -= step;
        }
        else break;
    }

    _focusBox.setModify(false);
    _singleton.frames[_frameId].setBox(_focusBox.getKey(), _focusBox);
}

void QWorkerThread::replicateBoundingBoxFromCore(Core &_singleton, const unsigned int _bboxKey, const unsigned int _numFrames)
{
    unsigned int nextFrameId = static_cast<unsigned int>(this->getFrameId());
    unsigned int frameLimit = std::min(nextFrameId + _numFrames, static_cast<unsigned int>(_singleton.frames.size()));

    BoundingBox bbox = _singleton.frames[nextFrameId - 1].getBoxByKey(_bboxKey);
    bbox.setModify(true);
    for(unsigned int frameIndex = nextFrameId; frameIndex < frameLimit; frameIndex++)
    {
        BoundingBox repBox = _singleton.frames[frameIndex].getBoxById(bbox.getId());
        if(!repBox.isValid())
        {
            _singleton.frames[frameIndex].addBox(bbox);
        }
    }
}

void QWorkerThread::replicateBoundingBoxFromCoreBackwards(Core &_singleton, const unsigned int _bboxKey, const unsigned int _numFrames)
{
    unsigned int currentFrameId = static_cast<unsigned int>(this->getFrameId() - 1);
    unsigned int frameLimit = std::max(static_cast<int>(currentFrameId - _numFrames), 0);

    BoundingBox bbox = _singleton.frames[currentFrameId].getBoxByKey(_bboxKey);
    for(unsigned int frameIndex = currentFrameId; frameIndex > frameLimit; frameIndex--)
    {
        BoundingBox repBox = _singleton.frames[frameIndex].getBoxById(bbox.getId());
        if(!repBox.isValid())
        {
            _singleton.frames[frameIndex].addBox(bbox);
        }
    }
}

void QWorkerThread::removeBoxSequenceFromCore(Core &_singleton, const unsigned int _bboxKey)
{
    bool isErased = false;
    unsigned int currentFrameId = static_cast<unsigned int>(this->getFrameId()) - 1;

    BoundingBox bbox = _singleton.frames[currentFrameId].getBoxByKey(_bboxKey);
    for(unsigned int frameIndex = (currentFrameId); frameIndex < _singleton.frames.size(); frameIndex++)
    {
        isErased = _singleton.frames[frameIndex].removeBoxById(bbox.getId());

        if(!isErased)
        {
            break;
        }
    }
}
