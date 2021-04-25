﻿/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: ellipseitem.cpp
\brief 演示用头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/8
*/

#include "ellipseitem.h"

#include <QPainter>

CGraphEllipseItem::CGraphEllipseItem(QGraphicsItem * parent /* = 0 */)
    :QGraphicsItem(parent) {
}


CGraphEllipseItem::~CGraphEllipseItem() {
}

void CGraphEllipseItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget/* = 0*/) {
	Q_UNUSED(widget);
	Q_UNUSED(option);
    painter->drawEllipse(boundingRect());
	
}
QRectF CGraphEllipseItem::boundingRect() const {
	QRectF boundRt(-m_width/2, -m_height/2, m_width, m_height);	
	return boundRt;
}
QPainterPath CGraphEllipseItem::shape() const {
	QPainterPath paintPath;
    paintPath.addRect(boundingRect());
	return paintPath;
}
