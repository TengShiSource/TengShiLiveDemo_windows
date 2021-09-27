#include "HistoryCourse.h"

HistoryCourse::HistoryCourse()
{

}

HistoryCourse::HistoryCourse(QJsonObject json)
{
    videoInfoList.clear();
    this->setCourseName(json.value("courseName").toString());
    this->setAvatarUrl(json.value("avatarUrl").toString());
    this->setNickName(json.value("nickName").toString());
    this->setAppId(json.value("appId").toInt());
    this->setStartTime(QDateTime::fromString(
                         json.value("startTime").toString(),"yyyy-MM-dd HH:mm:ss"));
    this->setEndTime(QDateTime::fromString(
                         json.value("endTime").toString(),"yyyy-MM-dd HH:mm:ss"));
    this->setCourseId(json.value("courseId").toInt());
    QJsonArray data=json.value("videoInfos").toArray();
    for(int i=0;i<data.count(); i++){
        QJsonObject videoInfoObject = data.at(i).toObject();
        VideoInfos* videoInfo=new VideoInfos(videoInfoObject);
        videoInfoList.append(videoInfo);
    }
}


QString HistoryCourse::getCourseName() const
{
    return courseName;
}

void HistoryCourse::setCourseName(const QString &value)
{
    courseName = value;
}

QString HistoryCourse::getAvatarUrl() const
{
    return avatarUrl;
}

void HistoryCourse::setAvatarUrl(const QString &value)
{
    avatarUrl = value;
}

QString HistoryCourse::getNickName() const
{
    return nickName;
}

void HistoryCourse::setNickName(const QString &value)
{
    nickName = value;
}

int HistoryCourse::getAppId() const
{
    return appId;
}

void HistoryCourse::setAppId(int value)
{
    appId = value;
}

QDateTime HistoryCourse::getStartTime() const
{
    return startTime;
}

void HistoryCourse::setStartTime(const QDateTime &value)
{
    startTime = value;
}

QDateTime HistoryCourse::getEndTime() const
{
    return endTime;
}

void HistoryCourse::setEndTime(const QDateTime &value)
{
    endTime = value;
}

int HistoryCourse::getCourseId() const
{
    return courseId;
}

void HistoryCourse::setCourseId(int value)
{
    courseId = value;
}

QList<VideoInfos *> HistoryCourse::getVideoInfoList() const
{
    return videoInfoList;
}

void HistoryCourse::setVideoInfoList(const QList<VideoInfos *> &value)
{
    videoInfoList = value;
}
