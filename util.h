#ifndef UTIL_H
#define UTIL_H
#include <QString>
#include <QJsonObject>
#include <QByteArray>
#include <QJsonDocument>

class Util
{
public:
    static QString getBaseApiUrl();
    static QString getUrl(QString uri);
    static QJsonObject byteArrayToJsonObject(QByteArray byteArray);
};

#endif // UTIL_H
