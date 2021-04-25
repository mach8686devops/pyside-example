/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.cpp
\brief 示例实现文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/
#include "dialog.h"
#include <QCheckBox>

CDialog::CDialog(QWidget* pParent) : QDialog(pParent) {
	ui.setupUi(this);
	//ui.m_pLabel2->setText(tr("i like text file!"));
	connect(ui.checkBox, &QCheckBox::clicked, this, &CDialog::onChecked);
}

CDialog::~CDialog() {
	
}

void CDialog::onChecked(bool checked) {
	QString str;
	if (checked) {
		str = "i am checked.";
	}
	else {
		str = "please check!";
	}
	ui.m_pLabel2->setText(tr(str.toLocal8Bit().data()));
}