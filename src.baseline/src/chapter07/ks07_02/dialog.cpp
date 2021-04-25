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
#include <QGridLayout>
#include <QPainter>

#include "dialog.h"
#include "customwidget.h"


CDialog::CDialog(QWidget* parent) : QDialog(parent)
{
	ui.setupUi(this);

	QGridLayout* gridLayout = new QGridLayout(ui.widget);
	gridLayout->setObjectName(QStringLiteral("gridLayout"));

	m_pWidget = new CCustomWidget(ui.widget);
	gridLayout->addWidget(m_pWidget, 0, 0);
}

