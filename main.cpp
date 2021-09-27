#include "mainwindow.h"
#include <QApplication>
#include <QProcess>
#include "util.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/app_icon.ico"));

    QString filePath = QCoreApplication::applicationDirPath() + "/cache.ini";
    QSettings configIni(filePath, QSettings::IniFormat);

//     winstu5+2:7  wintea5+2:6  winstulive 9   wintealive 8   windemo 3
    QString workpath = QApplication::applicationDirPath();
    QString checkUrl = Util::getUrl("/app/version?appType=3&versionCode="+QString::number(config->versionCode));
    NetWork network;
    QByteArray result = network.get(checkUrl);
    QJsonObject replyJson = Util::byteArrayToJsonObject(result);
    int code = replyJson.value("code").toInt();
    if(code == CODE_SUCCESS){
        QJsonObject data = replyJson.value("data").toObject();
        int versionCode = data.value("versionCode").toInt();
        if(versionCode > config->versionCode){

            //获取更新包URL
            QString pakUrl = data.value("appPath").toString();
            //打开更新程序
            QStringList arguments;
            arguments << "classDemo.exe";
            arguments << "classDemoTmp.exe";
            arguments << pakUrl;

            QString programFile = workpath+"/UpDate.exe";
            QFileInfo exeFile(programFile);
            if(exeFile.exists()){
                QProcess::startDetached(programFile, arguments);
                config->versionCode=versionCode;
                return 0;
            }

        }
    }


    MainWindow w;
    w.show();

    return a.exec();
}
