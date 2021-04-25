﻿/*! 
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

#include "widget.h"


CMainDialog::CMainDialog(QWidget* pParent) : QDialog(pParent) {
    ui.setupUi(this);
	initialDialog();
}

CMainDialog::~CMainDialog(){
	
}
void CMainDialog::initialDialog() {
	
	CWidget* pWidget = new CWidget(ui.widget);
    ui.gridLayout->addWidget(pWidget, 0, 0);
}