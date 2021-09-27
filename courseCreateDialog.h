#ifndef COURSECREATEDIALOG_H
#define COURSECREATEDIALOG_H


#include <QDialog>
#include <QButtonGroup>
#include <QLineEdit>

namespace Ui {
class CourseCreateDialog;
}

class CourseCreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CourseCreateDialog(QWidget *parent = 0);
    ~CourseCreateDialog();

    QLineEdit* edit_courseId;

private slots:
    void on_btn_ok_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::CourseCreateDialog *ui;
    QButtonGroup *recordRadio;
};

#endif // COURSECREATEDIALOG_H
