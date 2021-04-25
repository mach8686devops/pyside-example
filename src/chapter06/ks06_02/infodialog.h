#pragma once
#include <QDialog>

namespace Ui {
class CInfoDialog;
}

class CInfoDialog : public QDialog {
    Q_OBJECT

public:
    explicit CInfoDialog(QWidget *parent = nullptr);
    ~CInfoDialog();
private slots:
    /*
     *  @brief 单击允许编辑时对应的槽函数
     *  @param[in] b true:允许编辑, false:禁止编辑
     *  @return void
    */
    void slot_editEnabled(bool b);

private:
    Ui::CInfoDialog *ui;
};

