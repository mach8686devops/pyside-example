/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: listwidget.cpp
\brief	
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9 
*/
#include "listwidget.h"
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>

CListWidget::CListWidget(QWidget* parent) : QListWidget(parent) {
	setAcceptDrops(true);
}
void CListWidget::dragEnterEvent(QDragEnterEvent* event) {
	if (event->mimeData() && event->mimeData()->hasFormat("dnd/format")) {
		event->setDropAction(Qt::CopyAction);
		event->setAccepted(true);
	}
	else {
		event->setAccepted(false);
	}
}

void CListWidget::dragMoveEvent(QDragMoveEvent* event) {
	if (event->mimeData() && event->mimeData()->hasFormat("dnd/format")) {
		event->setDropAction(Qt::CopyAction);
		event->setAccepted(true);
	}
	else {
		event->setAccepted(false);
	}
}

void CListWidget::dragLeaveEvent(QDragLeaveEvent *event) {
	QListWidget::dragLeaveEvent(event); // 本案例中不需要处理dragLeaveEvent()。
										// 该事件可以用来执行一些撤销操作。
}

void CListWidget::dropEvent(QDropEvent *event) {
	if (event->mimeData() && event->mimeData()->hasFormat("dnd/format")) {
		QByteArray mimeData = event->mimeData()->data("dnd/format");
		QDomDocument document;
		document.setContent(mimeData); // 开始解析XML数据
		QDomElement rootDoc = document.firstChildElement();
		if (rootDoc.isNull() || (rootDoc.tagName() != "root")) // 检查XML数据是否为预期格式
			return;
		QDomElement eleDoc = rootDoc.firstChildElement();
		
		if (eleDoc.isNull() || (eleDoc.tagName() != "document"))// 判断格式的合法性
			return;
		QString strText = eleDoc.attribute("text");	// 解析拖放数据中的有效内容
		bool bBold = eleDoc.attribute("bold").toInt();
		QListWidgetItem* pItem = new QListWidgetItem(strText, this);
		QFont ft = pItem->font();
		ft.setBold(bBold);
		pItem->setFont(ft);
		addItem(pItem);
		event->setDropAction(Qt::CopyAction);
		event->setAccepted(true);
	}
}