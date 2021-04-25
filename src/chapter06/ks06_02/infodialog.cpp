#include "infodialog.h"
#include "ui_infodialog.h"

#include <QIntValidator>

CInfoDialog::CInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CInfoDialog) {
    ui->setupUi(this);

    connect(ui->ckEditable, &QCheckBox::stateChanged,
            this, &CInfoDialog::slot_editEnabled);
 
    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &CInfoDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected,
            this, &CInfoDialog::reject);

    // setValidator for leStature
    ui->leStature->setValidator(new QIntValidator(0, 300, ui->leStature)); // min:0cm, max:300cm

    // setMask for leBirthday, 年年年年-月月-日日
    ui->leBirthday->setInputMask("0000-00-00");
    ui->leBirthday->setText("00000000");
    ui->leBirthday->setCursorPosition(0);

    // mask & validator,单纯使用mask无法约束数值的范围
    QRegExp regExp("^1[3|4|5|8][0-9][0-9]{8}");
    ui->lePhone->setValidator(new QRegExpValidator(regExp, ui->lePhone));
    ui->lePhone->setInputMask("#00-000-00000000"); // eg. +86-135-87989898
    ui->lePhone->setText("+00-000-00000000");
}

CInfoDialog::~CInfoDialog()
{
    delete ui;
}


void CInfoDialog::slot_editEnabled(bool b){
    ui->leName->setEnabled(b);
    ui->leStature->setEnabled(b);
    ui->leBirthday->setEnabled(b);
    ui->lePhone->setEnabled(b);
}
