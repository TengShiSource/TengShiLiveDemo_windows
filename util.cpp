#include "util.h"

//生产环境
QString baseApiURL = "https://live.qmzhjy.com/live";
QString Util::getUrl(QString uri){
    return baseApiURL + uri;
}

QString Util::getBaseApiUrl(){
    return baseApiURL;
}

/**
 * @brief byteArrayToJsonObject QByteArray转换QJsonObject
 * @param byteArray 源数据QByteArray
 * @return
 */
QJsonObject Util::byteArrayToJsonObject(QByteArray byteArray){
    QJsonDocument jsonDocument = QJsonDocument::fromJson(byteArray);
    QJsonObject jsonObject = jsonDocument.object();
    return jsonObject;
}
