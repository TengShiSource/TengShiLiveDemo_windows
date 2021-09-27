#ifndef CONFIG_H
#define CONFIG_H

#include <QString>


class Config
{
public:
    QString appId;
    QString appSecret;
    QString timestamp;
    QString sign;
    QString appLogo;
    int versionCode=201;
//    QString versionName="2.0.1";

    QString token;
    QString userId;
    QString userName;

    QString lastCourseId;

};

extern Config *config;

#endif // CONFIG_H
