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
#include <QApplication>
#include <QDrag>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QMimeData>
#include <QPainter>
#include <QPaintEvent>
#include <QTextStream>


CTextEdit::CTextEdit(QWidget* parent) : QTextEdit(parent) {
	m_bDrag = false;
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

void CTextEdit::mousePressEvent(QMouseEvent *e) {
	QTextEdit::mousePressEvent(e);	// 调用基类接口
	m_ptMousePress = e->globalPos();// 记录鼠标坐标
	QTextCursor tc = textCursor();	// 获取光标下选中的文本对象
	if (tc.selectedText().length() > 0) // 满足拖放要求，则竖起标志
		m_bDrag = true;
}

void CTextEdit::mouseReleaseEvent(QMouseEvent *e) {
	QTextEdit::mouseReleaseEvent(e);// 调用基类接口
	m_bDrag = false;				// 把标志放倒
}

void CTextEdit::mouseMoveEvent(QMouseEvent *e) {
	emit(viewMouseMove(e));	// 发射信号，以便可以在状态栏显示鼠标坐标
	Qt::MouseButtons btns = e->buttons();
	if (!(btns | Qt::NoButton)) { 
		m_bDrag = false;	// 如果没有按下鼠标按键，则不允许拖放
	}
	bool bDistance = false;
	QPoint ptDistance = e->globalPos() - m_ptMousePress; // 计算鼠标移动的距离
	if (ptDistance.manhattanLength() > QApplication::startDragDistance()){ 
		bDistance = true;// 超过允许的拖放距离才启动拖放操作
	}
	if (m_bDrag &&		// 允许拖放
		bDistance &&	// 距离足够
		(btns & Qt::LeftButton)) { // 左键按下
		m_bDrag = false;// 先把标志放倒
		/* 开始准备拖放数据*/
		QTextCursor tc = textCursor();			// 获取光标下选中的文本对象
		QTextCharFormat textCharFormat = tc.charFormat(); // 获取它的格式
		bool b = textCharFormat.font().bold(); // 获取字体的粗体信息
		/* 构建拖放对象及数据 */
		QMimeData *mimeData = new QMimeData;
		QByteArray itemData;
		QTextStream textStream(&itemData, QIODevice::ReadWrite);
		textStream.setCodec("UTF-8");

		/* 使用XML格式组织拖放数据 */
		QDomDocument doc;
		QDomElement rootDoc = doc.createElement("root");
		doc.appendChild(rootDoc);
		QDomElement eleDoc = doc.createElement("document");
		eleDoc.setAttribute("text", tc.selectedText()); // 构建自定义属性数据
		eleDoc.setAttribute("bold", b);
		rootDoc.appendChild(eleDoc);
		doc.save(textStream, 1, QDomNode::EncodingFromTextStream);

		mimeData->setData("dnd/format", itemData); // "dnd/format"用来区分不同拖放数据
		QDrag *drag = new QDrag(this);
		drag->setMimeData(mimeData);
		if (drag->exec(Qt::DropActions(Qt::MoveAction | Qt::CopyAction), Qt::CopyAction) == Qt::CopyAction) {
			// 此处可以根据对方的返回值，执行不同的处理。
		}
	}
	else {
		QTextEdit::mouseMoveEvent(e); // 调用基类接口
	}	
}
bool CTextEdit::openFile(const QString& strFile) {
	QFile file;
	file.setFileName(strFile);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		return false;
	}
	QTextStream input(&file);
	input.setCodec("GBK"); // 读者可以试试用: UTF-8。

	QString str = input.readAll();
	setText(str);

	m_strFileName = strFile;	
	return true;
}