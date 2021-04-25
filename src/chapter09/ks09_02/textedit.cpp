/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: textedit.cpp
\brief CTextEdit的实现文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/8
*/

#include "textedit.h"
#include <QPainter>
#include <QPaintEvent>


CTextEdit::CTextEdit(QWidget* parent):QTextEdit(parent) {

}

void CTextEdit::paintEvent(QPaintEvent *event) {
	QPainter painter;
	painter.begin(viewport());
	// 设置反走样
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(Qt::blue);
	painter.fillRect(event->rect(), QBrush(Qt::yellow));

	// 设置字体
	QFont ft(QString::fromUtf8("宋体"), 18);
	painter.setFont(ft);
	painter.drawText(QPointF(100, 100), "file read ok!");

	painter.end();
	QTextEdit::paintEvent(event); // 需要放置在自定义绘制代码的后面，否则基类绘制的内容会被自定义绘制冲掉。
}
