#pragma once
#include <QDialog>

namespace Ui {
class CInfoDialog;
}

class CInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CInfoDialog(QWidget *parent = nullptr);
    ~CInfoDialog();
private slots:

private:
    Ui::CInfoDialog *ui;
};

