/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.cpp
\brief	
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9 

*/
#include "dialog.h"
#include <QGridLayout>
#include <QComboBox>
#include <QMessageBox>

// 用户角色枚举
enum EUserType {
    EUserType_Invalid=0,    // 无效
    EUserType_Admin,        // 管理员
    EUserType_User,         // 普通用户
    EUserType_Guest,        // guest用户
    EUserType_Other,        // 其他

    EUserType_Max
};

CDialog::CDialog(QWidget* parent) : QDialog(parent) {
	ui.setupUi(this);
    connect(ui.btnPopup, &QPushButton::clicked,
            this, &CDialog::slot_popup);

    connect(ui.cbRole, SIGNAL(currentIndexChanged(int)),
            this, SLOT(slot_cbRoleChanged(int)));

    connect(ui.buttonBox, &QDialogButtonBox::accepted,
            this, &CDialog::accept);
    connect(ui.buttonBox, &QDialogButtonBox::rejected,
            this, &CDialog::reject);


    // addItem, 当前第0条
    ui.cbRole->addItem("user", QVariant(static_cast<int>(EUserType_User)));

    // 当前第1条
    ui.cbRole->addItem("guest");
    ui.cbRole->setItemData(1, static_cast<int>(EUserType_Guest));

    ui.cbRole->addItem(QIcon(":/images/user.png"),
                       "other",
                       static_cast<int>(EUserType_Other));

    QStringList strList;
    strList<<"maintain" << "security" << "owner";
    ui.cbRole->addItems(strList);

    // 在user之前插入一条记录
    ui.cbRole->insertItem(0,        // 将在第0条之前插入
                          "admin",  // "admin"将变为第0条
                          static_cast<int>(EUserType_Admin));

}

void CDialog::slot_popup(bool b){
    Q_UNUSED(b);
    ui.cbRole->showPopup();
}


void CDialog::slot_cbRoleChanged(int idx) {
    QString str = ui.cbRole->currentText();
    int nUserType = ui.cbRole->itemData(idx).toInt();
    EUserType eUserType = static_cast<EUserType>(nUserType);

    QString strInfo;
    strInfo = str;
    strInfo += ",";
    strInfo += QString("idx=%1,usertype enum value=%2")
                        .arg(idx)
                        .arg(nUserType);

    switch (eUserType){
    case EUserType_Admin:
        QMessageBox::information(this,
                                 "combobox selection change",
                                 strInfo);
        break;
    default:
        break;
    }
}




