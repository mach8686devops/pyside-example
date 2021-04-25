/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.cpp
\brief	
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/7

*/
#include <QStackedLayout>
#include "dialog.h"
#include "step1.h"
#include "step2.h"
#include "step3.h"

CDialog::CDialog(QWidget* parent) : QDialog(parent) {
	ui.setupUi(this);  

    // 构建QStackedLayout布局对象、3个子向导界面对象。将堆栈布局添加到父窗口的布局对象中
    QStackedLayout* pStackedLayout = new QStackedLayout(ui.horizontalLayout);

    CStep1* pWidgetStep1 = new CStep1(this);
    CStep2* pWidgetStep2 = new CStep2(this);
    CStep3* pWidgetStep3 = new CStep3(this);

    // 将3个子向导界面对象添加到堆栈布局
    pStackedLayout->addWidget(pWidgetStep1);
    pStackedLayout->addWidget(pWidgetStep2);
    pStackedLayout->addWidget(pWidgetStep3);

    // 设置默认页
    pStackedLayout->setCurrentIndex(0);

    // 将堆栈布局添加到父窗口的布局对象中
    //ui.horizontalLayout->addLayout(pStackedLayout);

    // 绑定信号槽:将子向导界面的信号绑定到堆栈布局对象的槽函数
    connect(pWidgetStep1, &CStep1::sig_showPage, pStackedLayout, &QStackedLayout::setCurrentIndex);
    connect(pWidgetStep2, &CStep2::sig_showPage, pStackedLayout, &QStackedLayout::setCurrentIndex);
    connect(pWidgetStep3, &CStep3::sig_showPage, pStackedLayout, &QStackedLayout::setCurrentIndex);

    connect(pWidgetStep3, &CStep3::sig_closeWindow, this, &CDialog::close);


}