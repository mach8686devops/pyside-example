/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: step3.h
\brief  对话框编程示例, 预览窗口类定义头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/7
*/

#pragma once

#include <QWidget>

#include "ui_step3.h"

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

class CStep3 : public QWidget {
    Q_OBJECT

public:
    /// 构造函数
    CStep3(QWidget *parent = 0);

Q_SIGNALS:
    void sig_showPage(int page_index);// 用来通知QStackedLayout，显示哪一步骤。
    void sig_closeWindow();         // 用来通知关闭主窗口

private slots:
    void slot_previous();
    void slot_close();

private:
    Ui::CStep3 ui;
};



