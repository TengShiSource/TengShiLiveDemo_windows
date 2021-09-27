#ifndef HISTORYCOURSE_H
#define HISTORYCOURSE_H
#include <QString>
#include <QDateTime>
#include <QList>
#include "VideoInfos.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QPushButton>

class HistoryCourse
{
public:
    HistoryCourse();

    HistoryCourse(QJsonObject json);

    QString getCourseName() const;
    void setCourseName(const QString &value);

    QString getAvatarUrl() const;
    void setAvatarUrl(const QString &value);

    QString getNickName() const;
    void setNickName(const QString &value);

    int getAppId() const;
    void setAppId(int value);

    QDateTime getStartTime() const;
    void setStartTime(const QDateTime &value);

    QDateTime getEndTime() const;
    void setEndTime(const QDateTime &value);


    int getCourseId() const;
    void setCourseId(int value);

    QList<VideoInfos *> getVideoInfoList() const;
    void setVideoInfoList(const QList<VideoInfos *> &value);

private:
    QString courseName;
    QString avatarUrl;
    QString nickName = "";
    int appId;
    QDateTime startTime;
    QDateTime endTime;
    int courseId;
    QList<VideoInfos*> videoInfoList;
};

#endif // HISTORYCOURSE_H
