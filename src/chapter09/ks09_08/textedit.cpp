/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: textedit.cpp
\brief	
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9 
*/

#include "base/basedll/baseapi.h"
#include "textedit.h"
#include <QPainter>
#include <QPaintEvent>
#include <QTextStream>

CTextEdit::CTextEdit(QWidget* parent) : QTextEdit(parent) {
	setMouseTracking(true);
}

void CTextEdit::paintEvent(QPaintEvent *event) {	

	QPainter painter;
	painter.begin(viewport());
	painter.setRenderHint(QPainter::Antialiasing, true);
	
	painter.setPen(Qt::blue);

	painter.fillRect(event->rect(), QColor(0, 255, 255, 100));

	QFont ft("宋体", 18);
	ft.setItalic(true);
	painter.setFont(ft);
	painter.drawText(QPointF(100,100), "file read ok!");

	painter.end();
	QTextEdit::paintEvent(event);

}

void CTextEdit::mouseMoveEvent(QMouseEvent *e) {
	QTextEdit::mouseMoveEvent(e); // 首先，调用基类接口
//	QTextCursor curCursor = textCursor();
	emit(viewMouseMove(e));
}
bool CTextEdit::openFile(const QString& fileName) {
	QFile file;
	QString strFileName = ns_train::getFileName(fileName); // 将环境变量转换为目录。
	file.setFileName(strFileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		return false;
	}
	QTextStream input(&file);
	input.setCodec("UTF-8"); // 读者可以试试:GBK，该编码格式必须与文件的实际编码一致。
	QString str = input.readAll();
	setText(str);
	m_strFileName = strFileName;
	return true;
}