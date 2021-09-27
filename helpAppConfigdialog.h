#ifndef HELPAPPCONFIGDIALOG_H
#define HELPAPPCONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class HelpAppConfigDialog;
}

class HelpAppConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpAppConfigDialog(QWidget *parent = 0);
    ~HelpAppConfigDialog();

private:
    Ui::HelpAppConfigDialog *ui;
};

#endif // HELPAPPCONFIGDIALOG_H
