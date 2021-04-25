/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: customlabel.cpp
\brief	
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/11 
*/

#include "customlabel.h"
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QPointF>


CCustomLabel::CCustomLabel(QWidget* parent) :
	QLabel(parent) {
}


void CCustomLabel::enterEvent(QEvent *event) {
	QLabel::enterEvent(event);
	QString str = objectName();
	int idx = str.lastIndexOf("_"); // 找到项目编号
	str = str.left(idx);
	emit sig_enter(str);
}

void CCustomLabel::leaveEvent(QEvent *event) {
	QLabel::leaveEvent(event);
	QString str = objectName();
	int idx = str.lastIndexOf("_"); // 找到项目编号
	str = str.left(idx);
	emit sig_leave(str);
}
void CCustomLabel::mousePressEvent(QMouseEvent *event) {
	QLabel::mousePressEvent(event);
	QString str = objectName();
	int idx = str.lastIndexOf("_"); // 找到项目编号
	str = str.left(idx);
	emit sig_pressed(str);
}