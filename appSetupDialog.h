#ifndef APPSETUPDIALOG_H
#define APPSETUPDIALOG_H

#include <QDialog>

namespace Ui {
class AppSetupDialog;
}

class AppSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AppSetupDialog(QWidget *parent = 0);
    ~AppSetupDialog();
private slots:

    void on_AppSetupDialog_rejected();

    void on_btn_ok_clicked();

    void on_btn_help_clicked();

private:
    Ui::AppSetupDialog *ui;
};

#endif // APPSETUPDIALOG_H
