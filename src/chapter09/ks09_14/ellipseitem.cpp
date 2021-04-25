﻿/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: rectitem.cpp
\brief 演示用头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/8
*/

#include "rectitem.h"

#include <QPainter>

CGraphRectItem::CGraphRectItem(QGraphicsItem * parent /* = 0 */)
    :QGraphicsItem(parent) {
}


CGraphRectItem::~CGraphRectItem() {
}

void CGraphRectItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget/* = 0*/) {
	Q_UNUSED(widget);
    painter->drawPath(shape());
	
}
QRectF CGraphRectItem::boundingRect() const {
	QRectF boundRt(-m_width/2, -m_height/2, m_width, m_height);	
	return boundRt;
}
QPainterPath CGraphRectItem::shape() const {
	QPainterPath paintPath;
    paintPath.addRect(boundingRect());
	return paintPath;
}
