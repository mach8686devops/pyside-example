/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: customwidget.cpp
\brief	
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/11 
*/
#include "customwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QPointF>


CCustomWidget::CCustomWidget(QWidget* parent) :
	QFrame(parent) {
}


void CCustomWidget::enterEvent(QEvent *event) {
	QFrame::enterEvent(event);
	QString str = objectName();
	int idx = str.lastIndexOf("_"); // 找到项目编号
	str = str.left(idx);
	emit sig_enter(str);
}

void CCustomWidget::leaveEvent(QEvent *event) {
	QFrame::leaveEvent(event);
	QString str = objectName();
	int idx = str.lastIndexOf("_"); // 找到项目编号
	str = str.left(idx);
	emit sig_leave(str);
}
void CCustomWidget::mousePressEvent(QMouseEvent *event) {
	QFrame::mousePressEvent(event);
	QString str = objectName();
	int idx = str.lastIndexOf("_"); // 找到项目编号
	str = str.left(idx);
	emit sig_pressed(str);
}