#ifndef VIDEODIALOG_H
#define VIDEODIALOG_H

#include <QDialog>
#include <QPalette>
#include <QUrl>
#include <QVBoxLayout>
#include <WidgetRenderer.h>
#include <QtAV>
#include <QtAVWidgets>
#include <QtAV/AVPlayer.h>
#include <QJsonObject>
#include "HistoryCourse.h"
#include "VideoInfos.h"
#include <QList>
#include <QVBoxLayout>
#include <QIcon>
#include <QJsonDocument>

namespace Ui {
class VideoDialog;
}

class VideoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VideoDialog(QWidget *parent = nullptr);
    ~VideoDialog();

public slots:
    void playVideo(QString url);

    void itemClick();

    void synchroData(QJsonObject historyCourse);

    void on_btn_puase_clicked();
private:
    Ui::VideoDialog *ui;

    void addVideoItem();

    void closeEvent(QCloseEvent *event);

    QtAV::AVPlayer * player=nullptr;

    static HistoryCourse* historyCourse;

     QVBoxLayout* layout;

     QVBoxLayout* vLayout=nullptr;

     QtAV::VideoOutput* vo;

     bool isPause=false;
};

#endif // VIDEODIALOG_H
