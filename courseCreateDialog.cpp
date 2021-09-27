#include "courseCreateDialog.h"
#include "ui_courseCreateDialog.h"
#include "global.h"

CourseCreateDialog::CourseCreateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CourseCreateDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

    QDateTime curDateTime=QDateTime::currentDateTime();
    ui->edit_courseName->setText(config->userName+QStringLiteral("的课")+curDateTime.toString("MM-dd"));
    ui->edit_minutes->setText("20");

    recordRadio = new QButtonGroup(this);
    recordRadio->addButton(this->ui->radio_record_auto,1);
    recordRadio->addButton(this->ui->radio_record_manual,2);
    recordRadio->addButton(this->ui->radio_record_no,3);

}

CourseCreateDialog::~CourseCreateDialog()
{
    delete ui;
}

void CourseCreateDialog::on_btn_ok_clicked()
{
    QString minutes = ui->edit_minutes->text();
    int minutesInt = minutes.toInt();
    if(minutesInt<5 || minutesInt>300){
        QMessageBox::information(this,QStringLiteral("系统提示"),QStringLiteral("课程时长需要在5至300之间"));
        return;
    }

    QJsonObject json;
//    json.insert("appId", config->appId);
//    json.insert("appSecret", config->appSecret);
    json.insert("courseName",ui->edit_courseName->text());
    json.insert("teacherPwd", ui->edit_teacherPwd->text());
    json.insert("studentPwd", ui->edit_studentPwd->text());
    QDateTime startTime=QDateTime::currentDateTime();
    json.insert("startTime",startTime.toString("yyyy-MM-dd HH:mm:ss"));
    QDateTime endTime = startTime.addSecs(minutesInt*60);
    json.insert("endTime",endTime.toString("yyyy-MM-dd HH:mm:ss"));
    QJsonObject options;
    options.insert("recMethod",recordRadio->checkedId());
    json.insert("courseOptions", options);

    QJsonDocument doc;
    doc.setObject(json);
    QByteArray postArray = doc.toJson(QJsonDocument::Compact);

    //创建课程
    QString url = Util::getUrl("/lvbcourse/createCourse");
    NetWork network;
    QByteArray result = network.post(url,postArray);
    QJsonObject replyJson = Util::byteArrayToJsonObject(result);
    int code = replyJson.value("code").toInt();
    if(code == CODE_SUCCESS){
        QString courseId = QString::number(replyJson.value("data").toInt());
        QMessageBox::information(this,QStringLiteral("系统提示"),QStringLiteral("课堂创建成功，编号为:")+courseId);
        this->edit_courseId->setText(courseId);

        config->lastCourseId = courseId;
        QString iniFileName =QCoreApplication::applicationDirPath()+ "/cache.ini";
        QSettings configIni(iniFileName, QSettings::IniFormat);
        configIni.setValue("lastCourseId",config->lastCourseId);

        this->close();
    }else{
        QMessageBox::information(this,QStringLiteral("系统提示"),replyJson.value("msg").toString());
    }



}

void CourseCreateDialog::on_btn_cancel_clicked()
{
    close();
}
