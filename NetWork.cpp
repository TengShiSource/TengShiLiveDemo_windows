#include "NetWork.h"
#include "Config.h"

NetWork::NetWork(QObject *parent) : QObject(parent)
{

}

/**
 * @brief 获取一张网格图片
 * @param url 请求路径,通过URL可以带参数
 * @return
 */
QByteArray NetWork::image(QString url)
{
    return NetWork::getImage(url,NULL,2000);
}

/**
 * @brief Http get请求
 * @param url 请求路径
 * @param headers 请求头
 * @return
 */
QByteArray NetWork::getImage(QString url,QString headers,int timeout)
{
    QUrl reqUrl(url);
    QNetworkRequest request;
    QSslConfiguration conf = request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(conf);
    request.setUrl(reqUrl);
    /*request.setRawHeader("Authorization","Bearer "+(Config::user->getToken()).toUtf8());*///请求默认带token
    if(!headers.isNull() && !headers.isEmpty()){
        QStringList list = headers.split(",");
        for(int i=0;i<list.size();i++){
            QStringList para = list[i].split(":");
            QString key = para[0];
            QString value = para[1];
            request.setRawHeader(key.toUtf8(),value.toUtf8());
        }
    }
    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(request);

    QByteArray _result;
    QTime _t;//计时器
    _t.start();
    bool _timeout = false;
    while (!reply->isFinished()) {
        QApplication::processEvents();
        if (_t.elapsed() >= timeout) {
            _timeout = true;
            break;
        }
    }

    if (!_timeout && reply->error() == QNetworkReply::NoError) {
        _result = reply->readAll();
    }

    reply->deleteLater();

    return _result;

}

/**
 * @brief get Http get请求
 * @param url 请求路径
 * @return
 */
QByteArray NetWork::get(QString url)
{
    QUrl reqUrl(url);
    QNetworkRequest request;
    QSslConfiguration conf = request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(conf);
    request.setUrl(reqUrl);
    request.setRawHeader("token",config->token.toUtf8());
    request.setRawHeader("appKey",config->appId.toUtf8());
    request.setRawHeader("timestamp",config->timestamp.toUtf8());
    request.setRawHeader("sign",config->sign.toUtf8());
    reply = manager.get(request);

    QByteArray _result;
    QTime _t;
    _t.start();

    bool _timeout = false;

    while (!reply->isFinished()) {
        QApplication::processEvents();
        if (_t.elapsed() >= TIMEOUT) {
            _timeout = true;
            break;
        }
    }

    if (!_timeout && reply->error() == QNetworkReply::NoError) {
        _result = reply->readAll();
    }

    reply->deleteLater();

    return _result;

}

/**
 * @brief post Http post请求
 * @param url 请求路径
 * @param data 提交的数据（text、json、xml、html）
 * @return
 */
QByteArray NetWork::post(QString url,QByteArray data){
    return post(url,"",data);
}

/**
 * @brief post Http post请求
 * @param url 请求路径
 * @param headers 请求头参数，格式 "key:value,key2:value2"
 * @param data 提交的数据（text、json、xml、html）
 * @return
 */
QByteArray NetWork::post(QString url,QString headers,QByteArray data){
    QUrl reqUrl(url);
    QNetworkRequest request;
    QSslConfiguration conf = request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(conf);
    request.setUrl(reqUrl);
    request.setRawHeader("Content-Type","application/json");
    request.setRawHeader("token",config->token.toUtf8());
    request.setRawHeader("appKey",config->appId.toUtf8());
    request.setRawHeader("timestamp",config->timestamp.toUtf8());
    request.setRawHeader("sign",config->sign.toUtf8());
    if(!headers.isEmpty()&&!headers.isNull()){
        QStringList list = headers.split(",");
        for(int i=0;i<list.size();i++){
            QStringList para = list[i].split(":");
            QString key = para[0];
            QString value = para[1];
            request.setRawHeader(key.toUtf8(),value.toUtf8());
        }
    }

    reply = manager.post(request,data);

    QByteArray _result;
    QTime _t;
    _t.start();

    bool _timeout = false;

    while (!reply->isFinished()) {
        QApplication::processEvents();
        if (_t.elapsed() >= TIMEOUT) {
            _timeout = true;
            break;
        }
    }

    if (!_timeout && reply->error() == QNetworkReply::NoError) {
        _result = reply->readAll();
    }

    reply->deleteLater();

    return _result;
}

/**
 * @brief postFile Http post上传文件请求
 * @param url 请求路径
 * @param parameters 请求参数
 * @param fileUrl 文件路径
 * @return
 */
QByteArray NetWork::postFile(QString url,QString parameters,QString fileUrl){
    QUrl reqUrl(url);
    QNetworkRequest request;
    QSslConfiguration conf = request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(conf);
    request.setUrl(reqUrl);
    QStringList list = parameters.split(",");
    for(int i=0;i<list.size();i++){
        QStringList para = list[i].split(":");
        QString key = para[0];
        QString value = para[1];
        request.setRawHeader(key.toUtf8(),value.toUtf8());
    }
    QFile* compressedFile = new QFile(fileUrl);
    compressedFile->open(QIODevice::ReadOnly);
    connect(reply,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(updateUploadProgress(qint64,qint64)));
    //reply = manager.post(request,&compressedFile);

    QByteArray _result;
    QTime _t;
    _t.start();

    bool _timeout = false;

    while (!reply->isFinished()) {
        QApplication::processEvents();
        if (_t.elapsed() >= TIMEOUT) {
            _timeout = true;
            break;
        }
    }

    if (!_timeout && reply->error() == QNetworkReply::NoError) {
        _result = reply->readAll();
    }

    reply->deleteLater();

    return _result;
}

void NetWork::download(QString url,QString saveFileName){
    QByteArray array = get(url);
    QFile saveFile(saveFileName);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        return;
    }
    saveFile.write(array);
}

void NetWork::updateUploadProgress(qint64 bytesSent, qint64 bytesTotal){
    //Config::param->setBytesSent(bytesSent);
    //Config::param->setBytesTotal(bytesTotal);
}
