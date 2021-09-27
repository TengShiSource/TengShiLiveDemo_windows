#include "HistoryClassDialog.h"
#include "ui_HistoryClassDialog.h"

HistoryClassDialog::HistoryClassDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryClassDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

}

HistoryClassDialog::~HistoryClassDialog()
{
    delete ui;
}

void HistoryClassDialog::showEvent(QShowEvent *event){

    layout = new QVBoxLayout(ui->wgt_classList);
    getHistoryCourse();
}


//历史课程
void HistoryClassDialog::getHistoryCourse(){

    if(layout->count()!=0){
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != 0)
        {
//            layout->removeWidget(child->widget());
            child->widget()->setParent(nullptr);
            delete child->widget();
            delete child;
        }
        delete layout;
        layout = new QVBoxLayout(ui->wgt_classList);

      }

    QString url = "http://jledu.f3322.net:9208/live/member/getCourseVideoList?userId="+config->userId+"&userRole=t";
    NetWork network;
    QByteArray result = network.get(url);
    QJsonObject replyJson = Util::byteArrayToJsonObject(result);
    int code = replyJson.value("code").toInt();
     QJsonArray data;
    if(code == CODE_SUCCESS){
        data = replyJson.value(QStringLiteral("data")).toArray();
    }else{
        QMessageBox::information(this,QStringLiteral("系统提示"),replyJson.value("msg").toString());
        return;
    }
    qDebug()<<"-------"+QString(QJsonDocument(replyJson).toJson(QJsonDocument::Compact));



    if(data.count()>0){

       for(int i=0;i<data.count(); i++){
           QJsonObject courseObject = data.at(i).toObject();
           HistoryCourse* historyCourse=new HistoryCourse(courseObject);

           //行容器
           QWidget* itemWidget = new QWidget();
           itemWidget->setMinimumWidth(350);
           itemWidget->setMaximumHeight(150);
           itemWidget->setStyleSheet("background-color:#dadada;border-radius:6px;");
           QVBoxLayout* vLayout = new QVBoxLayout(itemWidget);
           vLayout->setMargin(5);

           QWidget* timeWidget = new QWidget();
           timeWidget->setMaximumHeight(20);
           QHBoxLayout* hLayout = new QHBoxLayout(timeWidget);
           hLayout->setMargin(0);

           QLabel* courseState = new QLabel();
           courseState->setMinimumWidth(60);
//           if(course->getStatus()==0){
//               courseState->setStyleSheet("background-image: url(:/images/img_onclose.png);border:0px;background-position:center left;background-origin:content;background-repeat:none;");
//           }else if(course->getStatus()==1){
//               courseState->setStyleSheet("background-image: url(:/images/img_onlive.png);border:0px;background-position:center left;background-origin:content;background-repeat:none;");
//           }

           QString date=historyCourse->getStartTime().toString("MM-dd");
           QString result = date.replace(QRegExp("-"), QStringLiteral("月"));
           QString startTime=historyCourse->getStartTime().toString("HH:mm");
           QString endTime=historyCourse->getEndTime().toString("HH:mm");
           QLabel* courseTime = new QLabel();
           courseTime->setText(result+QStringLiteral("日 ")+startTime+"-"+endTime);
           courseTime->setStyleSheet("border:0px;\nfont-size:13px;\nfont-family:\"Microsoft YaHei\",微软雅黑,\"SimHei\",黑体;");

           hLayout->addWidget(courseState);
           hLayout->addWidget(courseTime);
           hLayout->addStretch(1);


           QLabel* courseName = new QLabel();
           courseName->setText(historyCourse->getCourseName());
           courseName->setStyleSheet("border:0px;\nfont-size:16px;\nfont-family:\"Microsoft YaHei\",微软雅黑,\"SimHei\",黑体;text-align:left;");


           QWidget* teacherWidget = new QWidget();
           teacherWidget->setMaximumHeight(60);
           QHBoxLayout* tLayout = new QHBoxLayout(teacherWidget);
           tLayout->setMargin(0);


           QWidget* nameWidget = new QWidget();
           QHBoxLayout* nLayout = new QHBoxLayout(nameWidget);
           nLayout->setMargin(0);
           nLayout->setSpacing(0);

            QLabel* teacherIcon = new QLabel();
            teacherIcon->setMinimumWidth(50);
            teacherIcon->setMaximumWidth(50);
            teacherIcon->setMaximumHeight(50);
            teacherIcon->setMinimumHeight(50);
            QPixmap pixmap;
            pixmap.loadFromData(NetWork::image(historyCourse->getAvatarUrl()));
            teacherIcon->setPixmap(pixmap);
            teacherIcon->setScaledContents(true);
            teacherIcon->setAlignment(Qt::AlignCenter);
            teacherIcon->setStyleSheet("background-image: url(:/images/img_history.png);border:0px;background-position:center center;background-origin:content;background-repeat:none;");

            QWidget* tnWidget = new QWidget();
            tnWidget->setMaximumHeight(40);
            QVBoxLayout* tnLayout = new QVBoxLayout(tnWidget);
            tnLayout->setMargin(0);
            tnLayout->setSpacing(5);

            QLabel* name = new QLabel();
            name->setText(historyCourse->getNickName());
            name->setStyleSheet("border:0px;\nfont-size:13px;\nfont-family:\"Microsoft YaHei\",微软雅黑,\"SimHei\",黑体;text-align:left;");

            QLabel* lab = new QLabel();
            lab->setText(QStringLiteral("授课"));
            lab->setStyleSheet("border:0px;\nfont-size:13px;\nfont-family:\"Microsoft YaHei\",微软雅黑,\"SimHei\",黑体;text-align:left;");
            tnLayout->addWidget(name);
            tnLayout->addWidget(lab);

            nLayout->addWidget(teacherIcon);
            nLayout->addWidget(tnWidget);


           QPushButton* join=new QPushButton();
           join->setMinimumHeight(30);
           join->setMinimumWidth(100);
           join->setStyleSheet("border: 0;border-radius: 15px;padding: 0 5px;color: rgb(255, 255, 255);background-color: rgb(85, 170, 127);\nfont-family:\"Microsoft YaHei\",微软雅黑,\"SimHei\",黑体;");

            join->setText(QStringLiteral("课程回放"));
            join->setProperty("historyCourse",courseObject);
            connect(join, SIGNAL(clicked(bool)), this, SLOT(watchVideo()));

           tLayout->addWidget(nameWidget);
           tLayout->addStretch(1);
           tLayout->addWidget(join);


           vLayout->addWidget(timeWidget);
           vLayout->addWidget(courseName);
           vLayout->addWidget(teacherWidget);

           layout->addWidget(itemWidget);
           layout->setAlignment(Qt::AlignTop);

       }

    }else {
        QLabel* noCourse = new QLabel();
        noCourse->setMinimumWidth(200);
        noCourse->setMaximumWidth(200);
        noCourse->setMaximumHeight(200);
        noCourse->setMinimumHeight(200);
        noCourse->setStyleSheet("background-image: url(:/images/img_nocourse.png);border:0px;background-position:center center;background-origin:content;background-repeat:none;");
        layout->addWidget(noCourse);
        layout->setAlignment(Qt::AlignCenter);
    }
}

void HistoryClassDialog::watchVideo(){
    QPushButton *watchVideo = dynamic_cast<QPushButton*> (sender());
    if(watchVideo != Q_NULLPTR)
    {
        QJsonObject historyCourse = watchVideo->property("historyCourse").toJsonObject();
        if(videoDialog==nullptr){
          videoDialog=new VideoDialog();
          connect(this, SIGNAL(synchroData(QJsonObject)), videoDialog, SLOT(synchroData(QJsonObject)));
        }
        QDesktopWidget* desktopWidget = QApplication::desktop();
        QRect deskRect = desktopWidget->screenGeometry();
        int width=deskRect.width();
        int height=deskRect.height();
        videoDialog->resize(width,height);
        videoDialog->setModal(true);
        videoDialog->show();
        emit synchroData(historyCourse);
    }


}
