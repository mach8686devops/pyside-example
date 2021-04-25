/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: logdockwidget.cpp
\brief 日志窗口类实现文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9 
*/
#include "logdockwidget.h"
#include "logevt.h"
#include <QTableWidget>
#include <QHeaderView>

const int maxLogNum = 1000;	// 日志窗口显示的最大日志数目

CLogDockWidget::CLogDockWidget(const QString &title, QWidget *parent, Qt::WindowFlags flags) :
	QDockWidget(title, parent, flags), m_pTableWidget(NULL) {

	m_pTableWidget = new QTableWidget(this);
	m_pTableWidget->setColumnCount(3); // 日志级别、内容、时间
	QFont font = m_pTableWidget->horizontalHeader()->font();	
	font.setBold(true);
	m_pTableWidget->horizontalHeader()->setFont(font);// 设置表头字体加粗
	m_pTableWidget->horizontalHeader()->setFixedHeight(25); //设置表头的高度
	m_pTableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	m_pTableWidget->setHorizontalHeaderLabels(QStringList() << QString::fromLocal8Bit("级别") << QString::fromLocal8Bit("时间") << QString::fromLocal8Bit("内容"));
	m_pTableWidget->setColumnWidth(0, 100);
	m_pTableWidget->setColumnWidth(1, 100);
	m_pTableWidget->horizontalHeader()->setStretchLastSection(true); // 自动扩展最后一列
	m_pTableWidget->setShowGrid(false); //设置不显示格子线
	m_pTableWidget->verticalHeader()->setHidden(true);	// 设置垂直表头不可见
	QString strStyle = "QHeaderView::section{background:skyblue;}";
	m_pTableWidget->horizontalHeader()->setStyleSheet(strStyle); //设置表头背景色
	setWidget(m_pTableWidget);
}
CLogDockWidget::~CLogDockWidget() {

}
void CLogDockWidget::customEvent(QEvent* e) {
	CLogEvt* pLogEvt = dynamic_cast<CLogEvt*>(e);
	if (NULL != pLogEvt) {
		SLog log = pLogEvt->getLog();
		int rowIndex = m_pTableWidget->rowCount();
		while (rowIndex >= maxLogNum) { // 仅保留maxLogNumb个，需要删除最后的日志。
			m_pTableWidget->removeRow(rowIndex - 1);
			rowIndex--;
		}
		//新增的永远加到最前面
		m_pTableWidget->insertRow(0);
		m_pTableWidget->setItem(0, 0, new QTableWidgetItem(SLog::translateLevel(log.level)));
		m_pTableWidget->setItem(0, 1, new QTableWidgetItem(log.time.toString()));
		m_pTableWidget->setItem(0, 2, new QTableWidgetItem(log.msg));
	}
}