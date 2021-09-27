#include "VideoInfos.h"

VideoInfos::VideoInfos()
{

}

VideoInfos::VideoInfos(QJsonObject json)
{
    this->setId(json.value("id").toInt());
    this->setDuration(json.value("duration").toInt());
    this->setFileId(json.value("fileId").toString());
    this->setVideoUrl(json.value("videoUrl").toString());
    this->setCreateTime(QDateTime::fromString(
                         json.value("createTime").toString(),"yyyy-MM-dd HH:mm:ss"));
}

int VideoInfos::getId() const
{
    return id;
}

void VideoInfos::setId(int value)
{
    id = value;
}

int VideoInfos::getDuration() const
{
    return duration;
}

void VideoInfos::setDuration(int value)
{
    duration = value;
}

QString VideoInfos::getVideoUrl() const
{
    return videoUrl;
}

void VideoInfos::setVideoUrl(const QString &value)
{
    videoUrl = value;
}

QString VideoInfos::getFileId() const
{
    return fileId;
}

void VideoInfos::setFileId(const QString &value)
{
    fileId = value;
}

QDateTime VideoInfos::getCreateTime() const
{
    return createTime;
}

void VideoInfos::setCreateTime(const QDateTime &value)
{
    createTime = value;
}
