#include "dialogboundingbox.h"
#include "ui_dialogboundingbox.h"

DialogBoundingBox::DialogBoundingBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBoundingBox)
{
    this->ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    this->enterPressed = new QAction(tr("enter"), this);
    this->enterPressed->setShortcuts(QList<QKeySequence>() << Qt::EnterKeyDefault);
    this->addAction(enterPressed);

    this->qStandardModel = new QStandardItemModel(this);
    this->qTreeCompleter = new QTreeModelCompleter(this);
}

DialogBoundingBox::~DialogBoundingBox()
{
    delete ui;
}

void DialogBoundingBox::connectSignalSlots()
{
    this->connect(this->ui->spinBoxId,
                  SIGNAL(valueChanged(int)),
                  this,
                  SLOT(slot_spinBoxIdChanged(int))
                  );

    this->connect(this->ui->buttonBoxOKcancel,
                  SIGNAL(accepted()),
                  this,
                  SLOT(slot_buttonBoxAccepted())
                  );

    this->connect(this->ui->buttonBoxOKcancel,
                  SIGNAL(rejected()),
                  this,
                  SLOT(slot_buttonBoxRejected())
                  );
}

void DialogBoundingBox::initializeWidgets()
{
    // change widgets values
    BoundingBox bbox = this->singleton->frames[this->frameId].getBoxByKey(this->bboxKey);

    this->ui->spinBoxId->setMinimum(1);
    this->ui->spinBoxId->setMaximum(100000);

    // populate spinbox
    if(bbox.getId() > 0)
    {
        this->ui->spinBoxId->setValue(bbox.getId());
    }
    else
    {
        unsigned int idValue = this->singleton->frames[this->frameId].getBoxes().size();

        if(this->singleton->setup.getLatestCategory().empty())
        {
            this->ui->spinBoxId->setValue(idValue);
        }
        else
        {
            this->ui->spinBoxId->setValue(this->singleton->setup.getLatestId());
        }
    }

    this->ui->spinBoxX->setValue(bbox.getX());
    this->ui->spinBoxY->setValue(bbox.getY());
    this->ui->spinBoxW->setValue(bbox.getW());
    this->ui->spinBoxH->setValue(bbox.getH());

    this->ui->lineEditCategory->setCompleter(this->qTreeCompleter);
    this->ui->lineEditCategory->setText(QString::fromStdString(bbox.getCategory()));

    this->ui->plainTextEditInfo->clear();
    this->ui->plainTextEditInfo->appendPlainText(QString::fromStdString(bbox.getInfo()));
}

void DialogBoundingBox::stlToModel(Attribute* _nodeAtt, QStandardItem* _qParentItem)
{
    if(_nodeAtt != NULL)
    {
        QStandardItem* qNodeTag = new QStandardItem(QString::fromStdString((*_nodeAtt).getNodeName()));
        vector<Attribute*> nodeChildren = ((*_nodeAtt).getChildren());

        vector<Attribute*>::iterator childIt;
        for(childIt = nodeChildren.begin(); childIt != nodeChildren.end(); childIt++)
        {
            this->stlToModel(*childIt, qNodeTag);
        }
        _qParentItem->appendRow(qNodeTag);
    }
}

void DialogBoundingBox::slot_initializeDialog(Core &_singleton, const unsigned int _frameId, const unsigned int _bboxKey)
{
    this->singleton = &_singleton;
    this->bboxKey = _bboxKey;
    this->frameId = _frameId;

    vector<Attribute*> rootChildren = this->singleton->labelTree->getChildren();
    QStandardItem* qRootTag = new QStandardItem(QString::fromStdString(this->singleton->labelTree->getNodeName()));

    vector<Attribute*>::iterator childIt;
    for(childIt = rootChildren.begin(); childIt != rootChildren.end(); childIt++)
    {
        this->stlToModel(*childIt, qRootTag);
    }
    this->qStandardModel->appendRow(qRootTag);
    this->qTreeCompleter->setModel(this->qStandardModel);

    this->connectSignalSlots();
    this->initializeWidgets();
}

void DialogBoundingBox::slot_spinBoxIdChanged(int _value)
{
    BoundingBox bbox = this->singleton->frames[this->frameId].getBoxById(_value);
    if(bbox.isValid() && (this->bboxKey != bbox.getKey()))
    {
        this->ui->buttonBoxOKcancel->setEnabled(false);
    }
    else
    {
        this->ui->buttonBoxOKcancel->setEnabled(true);
    }
}

void DialogBoundingBox::slot_buttonBoxAccepted()
{
    BoundingBox bbox = BoundingBox(this->ui->spinBoxId->value(),
                                   this->bboxKey,
                                   this->ui->lineEditCategory->text().toStdString(),
                                   this->ui->plainTextEditInfo->toPlainText().toStdString(),
                                   std::string(),
                                   std::string(),
                                   this->ui->spinBoxX->value(),
                                   this->ui->spinBoxY->value(),
                                   this->ui->spinBoxW->value(),
                                   this->ui->spinBoxH->value()
                                   );

    this->singleton->frames[this->frameId].setBox(this->bboxKey, bbox);

    this->singleton->setup.setLargestId(bbox.getId());
    this->singleton->setup.setLatestCategory(bbox.getCategory());
    this->singleton->setup.setLatestId(bbox.getId());
    this->singleton->setup.setLatestLabel(bbox.getLabel());

    emit this->signal_updateFrame();
    this->accept();
}

void DialogBoundingBox::slot_buttonBoxRejected()
{
    emit this->signal_updateFrame();
    this->reject();
}
