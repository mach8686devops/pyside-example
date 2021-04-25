#include "infodialog.h"
#include "ui_infodialog.h"


CInfoDialog::CInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CInfoDialog)
{
    ui->setupUi(this);

}

CInfoDialog::~CInfoDialog()
{
    delete ui;
}


