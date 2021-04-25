/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.h
\brief 演示用头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/8 
*/

#pragma once

#include "ui_dialog.h"
#include <QDialog>


class CDialog : public QDialog {
	Q_OBJECT
public:
	CDialog(QWidget* parent);
	~CDialog(){;}
private slots:
    /*
     * @brief 单击弹出按钮时对应的槽函数
     * @param[in] b true:toogled(按钮为按下状态), false:not toogled(按钮为抬起状态)
    */
    void slot_popup(bool b);

    /*
     * @brief 组合框的值改变时对应的槽函数
     * @param[in] idx 当前新选中的项的下标
    */
    void slot_cbRoleChanged(int idx);

private:
	Ui::CDialog ui;
};


