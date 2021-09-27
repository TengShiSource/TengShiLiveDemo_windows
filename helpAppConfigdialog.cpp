#include "helpAppConfigdialog.h"
#include "ui_helpAppConfigdialog.h"

HelpAppConfigDialog::HelpAppConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpAppConfigDialog)
{
    ui->setupUi(this);
}

HelpAppConfigDialog::~HelpAppConfigDialog()
{
    delete ui;
}
