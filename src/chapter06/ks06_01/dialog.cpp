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
#include "customwidget.h"


CDialog::CDialog(QWidget* parent) : QDialog(parent) {
	ui.setupUi(this);

    // 构建占位widget内部的布局对象，以便嵌入子控件
    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    CCustomWidget* pCustomWidget = new CCustomWidget(this);
    gridLayout->addWidget(pCustomWidget); // 把子控件添加到布局

    ui.widget->setLayout(gridLayout); // 为占位widget设置布局

    ui.labelRight->setPixmap(QPixmap(":/images/pic1.png").scaled(300, 300));
}