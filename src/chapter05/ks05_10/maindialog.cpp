/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: maindialog.cpp
\brief  CMainDialog
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#include "maindialog.h"
#include <QGridLayout>

#include "widget.h" // 包含子控件头文件


CMainDialog::CMainDialog(QWidget* pParent) : QDialog(pParent) {
    ui.setupUi(this);
	initialDialog();
}

CMainDialog::~CMainDialog(){
	
}
void CMainDialog::initialDialog() {
    // 构造子控件
    CWidget* subWidget = new CWidget(ui.widget); // 占位控件作为parent

    // 构建占位控件内部的布局对象，否则拉伸时子控件无法跟随拉伸
    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    // 将子控件添加到布局
    gridLayout->addWidget(subWidget,  0, 0);

    // 为占位控件设置布局
    ui.widget->setLayout(gridLayout);
}