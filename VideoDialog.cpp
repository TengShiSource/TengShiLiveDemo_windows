#include "VideoDialog.h"
#include "ui_VideoDialog.h"
using namespace QtAV;
HistoryCourse* VideoDialog::historyCourse=nullptr;
VideoDialog::VideoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VideoDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
}

VideoDialog::~VideoDialog()
{
    delete ui;
}

void VideoDialog::synchroData(QJsonObject historyCourse){
     if(!historyCourse.isEmpty()){
         VideoDialog::historyCourse=new HistoryCourse(historyCourse);
         ui->lab_coursename->setText(VideoDialog::historyCourse->getCourseName());
         ui->lab_name->setText(VideoDialog::historyCourse->getNickName());
         addVideoItem();
         playVideo(VideoDialog::historyCourse->getVideoInfoList().at(0)->getVideoUrl());
     }

}

void VideoDialog::closeEvent(QCloseEvent *event){
    if(player!=nullptr){
        isPause=false;
        player->stop();
    }

}

void VideoDialog::addVideoItem(){
    QList<QPushButton*> btns = ui->wgt_videoItem->findChildren<QPushButton*>();
    foreach (QPushButton* btn, btns) {   delete btn;  }

    QList<VideoInfos*> videoItemList=VideoDialog::historyCourse->getVideoInfoList();
    if(vLayout==nullptr){
        vLayout = new QVBoxLayout(ui->wgt_videoItem);
        vLayout->setAlignment(Qt::AlignTop);
    }
       for(int i=0;i<videoItemList.size(); i++){
           VideoInfos* videoInfos=videoItemList.at(i);

           QPushButton* itemBtn=new QPushButton();
           itemBtn->setMinimumHeight(30);
           itemBtn->setMinimumWidth(100);
           itemBtn->setStyleSheet("border: 0;border-radius: 15px;padding: 0 5px;color: rgb(255, 255, 255);background-color: rgb(85, 170, 127);\nfont-family:\"Microsoft YaHei\",微软雅黑,\"SimHei\",黑体;");
            itemBtn->setText(QStringLiteral("第")+QString::number(i+1)+QStringLiteral("段"));
            itemBtn->setProperty("videoUrl",videoInfos->getVideoUrl());
            connect(itemBtn, SIGNAL(clicked(bool)), this, SLOT(itemClick()));
            vLayout->addWidget(itemBtn);

       }
}

void VideoDialog::itemClick(){
    QPushButton *itemBtn = dynamic_cast<QPushButton*> (sender());
    if(itemBtn != Q_NULLPTR)
    {
        QString videoUrl = itemBtn->property("videoUrl").toString();
        player->stop();
        playVideo(videoUrl);
    }


}

void VideoDialog::playVideo(QString url){

       if(player==nullptr){
          player=new AVPlayer(this);
          WidgetRenderer renderer;
          renderer.show();
          vo = new VideoOutput(this);

          Widgets::registerRenderers();
          player->setRenderer(vo);
          layout=new QVBoxLayout(ui->wgt_video);
          layout->addWidget(vo->widget());
       }

       player->play(url);	//填写要播放的视频的路径
       ui->btn_puase->setIcon(QIcon(":/images/img_play.png"));


}


void VideoDialog::on_btn_puase_clicked()
{
    if(!isPause){
        ui->btn_puase->setIcon(QIcon(":/images/img_puse.png"));
        player->pause(true);
        isPause=true;
    }else {
        ui->btn_puase->setIcon(QIcon(":/images/img_play.png"));
        player->pause(false);
        isPause=false;
}
}
