/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file ceditor.cpp
\brief CEditor实现文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/1
*/
#include <QtWidgets>

#include "editor.h"


CEditor::CEditor(QWidget *parent) : QLabel(parent) {
    setMouseTracking(true);
    setAutoFillBackground(true);
}

void CEditor::paintEvent(QPaintEvent *e) {
	QLabel::paintEvent(e);
    //QPainter painter(this);
	//painter.drawText(QPointF(0.f, 0.f), "")
    //myStarRating.paint(&painter, rect(), this->palette(),
    //                   StarRating::Editable);
}


void CEditor::mousePressEvent(QMouseEvent * /* event */) {
	if (text() == "Y")
		setText("N");
	else
		setText("Y");
    emit editingFinished();
}
