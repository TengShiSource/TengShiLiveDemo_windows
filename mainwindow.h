#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QCryptographicHash>
#include "HistoryClassDialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_appSetup_clicked();

    void on_btn_joinClass_clicked();

    void on_btn_createClass_clicked();

    void on_edit_courseId_textChanged(const QString &arg1);

    void on_radio_role_teacher_clicked();

    void on_radio_role_student_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QButtonGroup *roleRadio;

    QString coursePwd;//当前的课程的进入密码

    void readConfig();
    bool checkCourseId();
    void processCourseStatus();
};

#endif // MAINWINDOW_H
