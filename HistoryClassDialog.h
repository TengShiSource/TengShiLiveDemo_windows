#ifndef HISTORYCLASSDIALOG_H
#define HISTORYCLASSDIALOG_H

#include <QDialog>
#include "NetWork.h"
#include "global.h"
#include <QJsonObject>
#include <QJsonArray>
#include "HistoryCourse.h"
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRect>
#include <QDesktopWidget>
#include "VideoDialog.h"

namespace Ui {
class HistoryClassDialog;
}

class HistoryClassDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryClassDialog(QWidget *parent = nullptr);
    ~HistoryClassDialog();


signals:
    void synchroData(QJsonObject historyCourse);

private slots:
   void watchVideo();

private:
    Ui::HistoryClassDialog *ui;


    QVBoxLayout*layout;

    VideoDialog *videoDialog;

    void showEvent(QShowEvent * event);

    void getHistoryCourse();
};

#endif // HISTORYCLASSDIALOG_H
