#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "appSetupDialog.h"
#include "courseCreateDialog.h"
#include "global.h"
#include "QDir"
#include "QProcess"
#include <QSettings>
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //处理单选框
    roleRadio = new QButtonGroup(this);
    roleRadio->addButton(this->ui->radio_role_teacher,1);
    roleRadio->addButton(this->ui->radio_role_student,2);
    ui->edit_debug->hide();

    //初始化环境
    readConfig();


}

void MainWindow::readConfig(){
    //本地存储信息
    QString iniFileName = QCoreApplication::applicationDirPath() + "/cache.ini";
    QSettings configIni(iniFileName, QSettings::IniFormat);

    //初始配置
    config->appId = configIni.value("appId").toString();
    config->appSecret = configIni.value("appSecret").toString();
    config->userId = configIni.value("userId").toString();
    config->userName = configIni.value("userName").toString();
    config->lastCourseId = configIni.value("lastCourseId").toString();

    //当前时间
    QDateTime currentTime=QDateTime::currentDateTime();
    int ctime = currentTime.toTime_t();
    config->timestamp=QString::number(ctime);
    QString signStr=config->appId+config->appSecret+QString::number(ctime);
    config->sign=QCryptographicHash::hash(signStr.toLatin1(),QCryptographicHash::Md5).toHex().toUpper();

    //初始页面状态
    QPixmap pixmap;
    pixmap.loadFromData(NetWork::image(configIni.value("appLogo").toString()));
    pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->logo_index->setPixmap(pixmap);
    ui->lab_appName->setText(configIni.value("appName").toString());
    //设置状态栏标题
    this->setWindowTitle(configIni.value("appName").toString());
    ui->label_courseName->setText("");
    ui->label_courseStatus->setText("");
    ui->edit_coursePwd->hide();
    ui->label_coursePwd->hide();
    ui->btn_joinClass->setEnabled(false);
    ui->btn_joinClass->setStyleSheet(style_btn_disable);

    //如果没有应用配置，则打开配置页面
    if(config->appId.isEmpty()||config->appId.isNull()){
        on_btn_appSetup_clicked();
        readConfig();
        return;
    }else{
        //检查APPID与密钥是否失效     
        //验证应用配置
        QString url = Util::getUrl("/app/getAppInfo");
        NetWork network;
        QByteArray result = network.get(url);
        QJsonObject replyJson = Util::byteArrayToJsonObject(result);
        int code = replyJson.value("code").toInt();
        if(code != CODE_SUCCESS){
            on_btn_appSetup_clicked();
            readConfig();
            return;
        }

        //默认显示最后一次上过的课
        if(!config->lastCourseId.isEmpty()&&!config->lastCourseId.isNull()){
            ui->edit_courseId->setText(config->lastCourseId);
        }

        ui->label_userId->setText(QStringLiteral("用户ID : ") + config->userId);
        ui->label_username->setText(QStringLiteral("昵称 : ")+config->userName);
    }


}



//处理课堂状态
void MainWindow::processCourseStatus(){

    ui->label_courseName->setText("");
    ui->label_courseStatus->setText("");

    ui->edit_coursePwd->hide();
    ui->label_coursePwd->hide();
    ui->btn_joinClass->setEnabled(false);
    ui->btn_joinClass->setStyleSheet(style_btn_disable);
    QString courseId = ui->edit_courseId->text();
    if(courseId.isNull()||courseId.isEmpty())return;

    QString url = Util::getUrl("/lvbcourse/getCourseParam");
    url += "?courseId="+courseId;
    NetWork network;
    QByteArray result = network.get(url);
    QJsonObject replyJson = Util::byteArrayToJsonObject(result);
    int code = replyJson.value("code").toInt();
    if(code == CODE_SUCCESS){
        QJsonObject dataJson = replyJson.value("data").toObject();
        int courseStatus = dataJson.value("status").toInt();
        if(courseStatus<1){
            if(courseStatus==0){//未开始
                ui->label_courseStatus->setText(QStringLiteral("未开始"));
            }else{
                ui->label_courseStatus->setText(QStringLiteral("上课中"));
            }
            ui->label_courseStatus->setStyleSheet("color:#28b28b");
            ui->label_courseName->show();
            ui->label_courseName->setText(dataJson.value("courseName").toString());
            ui->label_courseName->setStyleSheet("color:#28b28b");
            ui->btn_joinClass->setEnabled(true);
            ui->btn_joinClass->setStyleSheet(style_btn_enable);
            //根据选择的身份确定是否显示密码框
            if(roleRadio->checkedId() == 1){//老师
                coursePwd = dataJson.value("teacherPwd").toString();
            }else{//学生
                coursePwd = dataJson.value("studentPwd").toString();
            }
            if(!coursePwd.isNull()&&!coursePwd.isEmpty()){
                ui->label_coursePwd->show();
                ui->edit_coursePwd->show();
            }else {
                ui->edit_coursePwd->setText("");
            }

        }else{//已结束
            ui->label_courseStatus->setText(QStringLiteral("已结束"));
            ui->label_courseStatus->setStyleSheet("color:#ff0000");
            ui->label_courseName->show();
            ui->label_courseName->setText(dataJson.value("courseName").toString());
            ui->label_courseName->setStyleSheet("color:#ff0000");
        }

        //config->appLogo = replyJson.value("data").toObject().value("appLogo").toString();
    }else{
        ui->label_courseName->setText(replyJson.value("msg").toString());
        ui->label_courseName->setStyleSheet("color:#ff0000");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

//APP应用调置
void MainWindow::on_btn_appSetup_clicked()
{
    AppSetupDialog *appSteup = new AppSetupDialog();
    appSteup->setModal(true);
    appSteup->exec();
    ui->label_userId->setText(QStringLiteral("用户ID : ") + config->userId);
    ui->label_username->setText(QStringLiteral("昵称 : " )+ config->userName);
}

//进入教室
void MainWindow::on_btn_joinClass_clicked()
{
    //验证一下课程编号
    processCourseStatus();
    if(!ui->btn_joinClass->isEnabled())return;
    QString inputPwd = ui->edit_coursePwd->text();
    if(QString::compare(inputPwd,this->coursePwd)!=0){
        QMessageBox::information(this,QStringLiteral("系统提示"),QStringLiteral("课堂密码输入错误"));
        return;
    }

    QJsonObject json;
    json.insert("id", config->userId);
    json.insert("courseId", ui->edit_courseId->text());
    json.insert("password", ui->edit_coursePwd->text());
    json.insert("nickName", config->userName);
    json.insert("role", roleRadio->checkedId()==1?"t":"s");
    QJsonDocument doc;
    doc.setObject(json);
    QByteArray postArray = doc.toJson(QJsonDocument::Compact);
    QString url = Util::getUrl("/member/registUser");
    NetWork network;
    QByteArray result = network.post(url,postArray);
    QJsonObject replyJson = Util::byteArrayToJsonObject(result);
    int code = replyJson.value("code").toInt();
    if(code != CODE_SUCCESS){
        QMessageBox::information(this,QStringLiteral("系统提示"),replyJson.value("msg").toString());
        return;
    }
    config->lastCourseId = ui->edit_courseId->text();
    QString iniFileName = QCoreApplication::applicationDirPath() + "/cache.ini";
    QSettings configIni(iniFileName, QSettings::IniFormat);
    configIni.setValue("lastCourseId",config->lastCourseId);

    config->token = replyJson.value("data").toString();
    //打开直播间
    QStringList arguments;
    arguments << config->token;
    arguments << Util::getBaseApiUrl();
    QString workpath = QApplication::applicationDirPath();
    if(QString::compare(workpath,
                       "D:/project/qmClassDemo/build-classDemo-Desktop_Qt_5_12_9_MSVC2017_32bit-Release/release")
            ==0){
        ui->edit_debug->setText(config->token);
        ui->edit_debug->show();
//        return;
    }

    //QString workpath = QApplication::applicationDirPath();
//    QString programFile = "D:/project/classroom_v2/build-TeacherStudio-Desktop_Qt_5_12_9_MSVC2017_32bit-Debug/debug/TeacherStudio.exe";
//    QString programFile = "D:/project/classroom_v2/build-TeacherStudio-Desktop_Qt_5_12_9_MSVC2017_32bit-Release/release/TeacherStudio.exe";
    QString programFile = workpath+"/TeacherStudio.exe";
    QFileInfo exeFile(programFile);
    if(exeFile.exists()){
        QProcess::startDetached(programFile, arguments);
    }else{
        QMessageBox::information(this,QStringLiteral("系统提示"),QStringLiteral("未找到程序文件"));
    }

}

//创建课堂
void MainWindow::on_btn_createClass_clicked()
{
    CourseCreateDialog *dialog = new CourseCreateDialog();
    dialog->edit_courseId = this->ui->edit_courseId;
    dialog->setModal(true);
    dialog->show();
}

//修改课程编号时处发自动检验课程状态
void MainWindow::on_edit_courseId_textChanged(const QString &arg1)
{
    if(ui->edit_courseId->text().length()==8){
        processCourseStatus();
    }
}

void MainWindow::on_radio_role_teacher_clicked()
{
    processCourseStatus();
}

void MainWindow::on_radio_role_student_clicked()
{
    processCourseStatus();
}

void MainWindow::on_pushButton_clicked()
{
    HistoryClassDialog *historyClassDialog = new HistoryClassDialog();
    historyClassDialog->setModal(true);
    historyClassDialog->exec();
}
