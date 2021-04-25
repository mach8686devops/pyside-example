/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: custombar.cpp
\brief	
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/11 
*/
#include "custombar.h"
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QPointF>


CCustomBar::CCustomBar(QWidget* parent) : 
	QFrame(parent),
	m_dMin(0.f),
	m_dMax(0.f),
	m_dValue(0.f) {
}

void CCustomBar::setValue(qreal min, qreal max, qreal value) {
	m_dMin = min;
	m_dMax = max;
	m_dValue = value;
	update();
}
void CCustomBar::enterEvent(QEvent *event) {
	QFrame::enterEvent(event);
	QString str = objectName();
	int idx = str.lastIndexOf("_"); // 找到项目编号
	str = str.left(idx);
	emit sig_enter(str);
}

void CCustomBar::leaveEvent(QEvent *event) {
	QFrame::leaveEvent(event);
	QString str = objectName();
	int idx = str.lastIndexOf("_"); // 找到项目编号
	str = str.left(idx);
	emit sig_leave(str);
}

void CCustomBar::paintEvent(QPaintEvent *event){
	QFrame::paintEvent(event);
	QSizeF sizeWidget = geometry().size();
	if (qAbs(m_dMax - m_dMin) < 0.001)	{
		return;
	}

    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
	QRectF rct(2, 2, (m_dValue - m_dMin) /(m_dMax - m_dMin)*sizeWidget.width()-4, sizeWidget.height()-4);
	QBrush brsh;
	brsh.setStyle(Qt::SolidPattern);
	brsh.setColor(QColor(17, 149, 189));
	painter.setBrush(brsh);
	painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rct, 5, 5);
	painter.end();
}

