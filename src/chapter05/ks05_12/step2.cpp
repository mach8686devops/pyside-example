/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: step2.cpp
\brief  对话框编程示例, 预览窗口类实现文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/7
*/


#include "step2.h"

CStep2::CStep2(QWidget *parent)
    : QWidget(parent) {
    ui.setupUi(this); 

    connect(ui.btnPrevious, &QPushButton::clicked,
        this, &CStep2::slot_previous);

    connect(ui.btnNext, &QPushButton::clicked,
        this, &CStep2::slot_next);

}

void CStep2::slot_previous() {
    emit sig_showPage(0); // 序号从0开始, step2界面是第1个，所以上一步要显示第0个。
}

void CStep2::slot_next() {
    emit sig_showPage(2); // 序号从0开始, step2界面是第1个，所以下一步要显示第2个。

}