#include "appSetupDialog.h"
#include "ui_appSetupDialog.h"
#include "QMessageBox.h"
#include "global.h"
#include "helpAppConfigdialog.h"

AppSetupDialog::AppSetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppSetupDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

//    ui->edit_appId->setText(config->appId);
//    ui->edit_appSecret->setText(config->appSecret);
    ui->edit_appId->setText("TZIYUNOA4L");
    ui->edit_appSecret->setText("7YFJQQXZBP");
    config->appId = "TZIYUNOA4L";
    config->appSecret = "7YFJQQXZBP";
    //当前时间
    QDateTime currentTime=QDateTime::currentDateTime();
    int ctime = currentTime.toTime_t();
    config->timestamp=QString::number(ctime);
    QString signStr=config->appId+config->appSecret+QString::number(ctime);
    config->sign=QCryptographicHash::hash(signStr.toLatin1(),QCryptographicHash::Md5).toHex().toUpper();

    //初始化用户ID与昵称
    QString iniFileName = QCoreApplication::applicationDirPath() + "/cache.ini";
    QSettings configIni(iniFileName, QSettings::IniFormat);
    if(config->userId.isNull()||config->userId.isEmpty()){
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);
        QString id = "";
        for(int i=0;i<8;i++){
            id += QString::number(qrand()%10);
        }
        config->userId = id;
        configIni.setValue("userId",config->userId);
    }
    if(config->userName.isNull()||config->userName.isEmpty()){
        config->userName = QStringLiteral("未命名");
        configIni.setValue("userName",config->userName);
    }
    ui->edit_userId->setText(config->userId);
    ui->edit_userName->setText(config->userName);
}

AppSetupDialog::~AppSetupDialog()
{
    delete ui;
}

void AppSetupDialog::on_AppSetupDialog_rejected()
{
    QString iniFileName = QCoreApplication::applicationDirPath() + "/cache.ini";
    QSettings configIni(iniFileName, QSettings::IniFormat);
    QString appId=configIni.value("appId").toString();
    if(appId.isNull()||appId.isEmpty()){
        QMessageBox::StandardButton result = QMessageBox::information(this, QStringLiteral("系统提示"), QStringLiteral("您还没有正确的配置应用信息，是否退出？"),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(result == QMessageBox::Yes){
           exit(0);
        }
    }else{
        this->close();
    }
}

void AppSetupDialog::on_btn_ok_clicked()
{
    QString appId = ui->edit_appId->text();
    QString appSecret = ui->edit_appSecret->text();
    QString userId = ui->edit_userId->text();
    QString userName = ui->edit_userName->text();
    ui->label_info->setText("");
    if(appId.isNull()||appId.isEmpty()){
        ui->label_info->setText(QStringLiteral("应用ID不可以为空"));
        return;
    }
    if(appSecret.isNull()||appSecret.isEmpty()){
        ui->label_info->setText(QStringLiteral("应用密钥不可以为空"));
        return;
    }
    if(userId.isNull()||userId.isEmpty()){
        ui->label_info->setText(QStringLiteral("用户ID不可以为空"));
        return;
    }
    if(userName.isNull()||userName.isEmpty()){
        ui->label_info->setText(QStringLiteral("昵称不可以为空"));
        return;
    }

    //验证应用配置
    QString url = Util::getUrl("/app/getAppInfo");
    NetWork network;
    QByteArray result = network.get(url);
    QJsonObject replyJson = Util::byteArrayToJsonObject(result);
    int code = replyJson.value("code").toInt();
    QJsonObject data=replyJson.value("data").toObject();
    if(code == CODE_SUCCESS){
        //保存应用设置
        config->appId = appId;
        config->appSecret = appSecret;
        config->userId = userId;
        config->userName = userName;
        QString iniFileName = QCoreApplication::applicationDirPath() + "/cache.ini";
        QSettings configIni(iniFileName, QSettings::IniFormat);
        configIni.setValue("appId",appId);
        configIni.setValue("appSecret",appSecret);
        configIni.setValue("userId",userId);
        configIni.setValue("userName",userName);
        configIni.setValue("appName",data.value("appName").toString());
        configIni.setValue("appLogo",data.value("appLogo").toString());

        QMessageBox::information(this,QStringLiteral("系统提示"),QStringLiteral("恭喜您，设置成功！"));
        this->close();

    }else{
        ui->label_info->setText(replyJson.value("msg").toString());
    }

}

void AppSetupDialog::on_btn_help_clicked()
{
    HelpAppConfigDialog *dialog = new HelpAppConfigDialog();
    dialog->setModal(true);
    dialog->exec();
}
