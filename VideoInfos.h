#ifndef VIDEOINFOS_H
#define VIDEOINFOS_H
#include <QString>
#include <QDateTime>
#include <QJsonObject>

class VideoInfos
{
public:
    VideoInfos();
    VideoInfos(QJsonObject json);
    int getId() const;
    void setId(int value);

    int getDuration() const;
    void setDuration(int value);

    QString getVideoUrl() const;
    void setVideoUrl(const QString &value);

    QString getFileId() const;
    void setFileId(const QString &value);

    QDateTime getCreateTime() const;
    void setCreateTime(const QDateTime &value);

private:
    int id;
    int duration;
    QString videoUrl;
    QString fileId;
    QDateTime createTime;
};

#endif // VIDEOINFOS_H
