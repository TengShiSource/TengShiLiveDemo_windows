#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QApplication>
#include <QFile>

/**
 *  Http请求
 *  2021.03.18  QiYing
 */

class NetWork : public QObject
{
    Q_OBJECT
public:
    explicit NetWork(QObject *parent = nullptr);


    /**
     * @brief Http 获取一张网络网片
     * @param url 请求路径,通过URL可以带参数
     * @return
     */
     static QByteArray image(QString url);

     /**
      * @brief Http get请求
      * @param url 请求路径
      * @param headers 请求参数
      * @param timeout 超时时间，单位ms
      * @return
      */
     static QByteArray getImage(QString url,QString headers,int timeout);

    /**
     * @brief get Http get请求
     * @param url 请求路径
     * @return
     */
    QByteArray get(QString url);

    /**
     * @brief post Http post请求
     * @param url 请求路径
     * @param data 提交的数据（text、json、xml、html）
     * @return
     */
    QByteArray post(QString url,QByteArray data);

    /**
     * @brief post Http post请求
     * @param url 请求路径
     * @param data 提交的数据（text、json、xml、html）
     * @return
     */
    QByteArray post(QString url,QString parameters,QByteArray data);

    /**
     * @brief postFile Http post上传文件请求
     * @param url 请求路径
     * @param headers 请求头参数，格式 "key:value,key2:value2"
     * @param fileUrl 文件路径
     * @return
     */
    QByteArray postFile(QString url,QString parameters,QString fileUrl);

    void download(QString url,QString saveFileName);

signals:

public slots:
    void updateUploadProgress(qint64 bytesSent, qint64 bytesTotal);
private:
    const int TIMEOUT = (30 * 1000);        //同步请求等待时间

    QNetworkAccessManager manager;

    QNetworkReply* reply;
};

#endif // NETWORK_H
