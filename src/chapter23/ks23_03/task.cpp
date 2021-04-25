/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: task.cpp
\brief	
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/11 
*/
#include "task.h"
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QPointF>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include "config.h"

CWidgetTask::CWidgetTask(QWidget* parent, int nState) :
	QFrame(parent),
	m_nEstimateWorkload(0),
	m_nBacklogId(-1),
	m_nId(-1),
	m_nState(nState) {
	ui.setupUi(this);

	if (ETaskState_Todo == nState) {
		ui.btnFinished->hide();
	}
	else if (ETaskState_Doing == nState) {
		ui.btnAccept->hide();
		ui.btnSave->hide();
	}
	else if (ETaskState_Finished == nState) {
		ui.btnSave->hide();
		ui.btnAccept->hide();
		ui.btnFinished->hide();
	}
	connect(ui.btnSave, &QPushButton::clicked, this, &CWidgetTask::slot_save);
	connect(ui.btnAccept, &QPushButton::clicked, this, &CWidgetTask::slot_accept);
	connect(ui.btnFinished, &QPushButton::clicked, this, &CWidgetTask::slot_finish);
}

void CWidgetTask::enterEvent(QEvent *event){
	QFrame::enterEvent(event);
	QString str = objectName();
	int idx = str.lastIndexOf("_"); // 找到编号
	str = str.left(idx);
	emit sig_enter(str);
}

void CWidgetTask::leaveEvent(QEvent *event) {
	QFrame::leaveEvent(event);
	QString str = objectName();
	int idx = str.lastIndexOf("_"); // 找到编号
	str = str.left(idx);
	emit sig_leave(str);
}
void CWidgetTask::setId(int id) {
	m_nId = id;
	ui.labelTask->setText(tr("task:%1").arg(id));
}
void CWidgetTask::setEstimateWorkload(int days) {
	m_nEstimateWorkload = days;
	ui.leEstimatedWorkload->setText(QString("%1").arg(days));
}
void CWidgetTask::setTask(const QString& str) {
	m_strTask = str;
	ui.pleTask->setPlainText(str);
}
void CWidgetTask::slot_save() {
	m_strDeveloper = CConfig::instance().getUser();
	if (m_strDeveloper.isEmpty()) {
		QMessageBox::information(this, tr("task"), tr("please login"));
		return;
	}
	save();
	emit sig_refresh();
}
void CWidgetTask::save() {
	QString strTask = ui.pleTask->toPlainText();
	m_nEstimateWorkload = ui.leEstimatedWorkload->text().toInt();
	qDebug() << strTask;
	QSqlQuery sql_query;
	QString strSql;
	strSql = "update tasks set task=:task, workloade=:workloade where id=:id";
	sql_query.prepare(strSql);
	sql_query.bindValue(":task", strTask);// backlog
	sql_query.bindValue(":workloade", m_nEstimateWorkload); // 估计工作量
	sql_query.bindValue(":id", m_nId); // id

	sql_query.exec();	// 插入记录
	qDebug() << sql_query.lastError();
}
void CWidgetTask::slot_accept() {
	m_strDeveloper = CConfig::instance().getUser();
	if (m_strDeveloper.isEmpty()) {
		QMessageBox::information(this, tr("task"), tr("please login"));
		return;
	}
	save();

	QSqlQuery sql_query;
	QString strSql;
	strSql = "update tasks set state=:state, developer=:developer where id=:id";
	sql_query.prepare(strSql);
	sql_query.bindValue(":state", ETaskState_Doing);// state
	sql_query.bindValue(":developer", m_strDeveloper);// developer
	sql_query.bindValue(":id", m_nId); // id
	sql_query.exec();	// 执行

	emit sig_refresh();
}
void CWidgetTask::setDeveloper(const QString& strDeveloper) {
	m_strDeveloper = strDeveloper;
	QByteArray byteArray;
	QSqlQuery sql_query;
	QString strSql;
	strSql = "select photo from users where name = \'";
	strSql += strDeveloper;
	strSql += "\'";
	qDebug() << strSql;
	if (sql_query.exec(strSql)) {
		//int role = 0;
		if (sql_query.first()) {
			byteArray = sql_query.value(0).toByteArray();
		}
		else {
			qDebug() << sql_query.lastError();
		}
	}
	else {
		qDebug() << sql_query.lastError();
	}

	QPixmap pixmap;
	pixmap.loadFromData(byteArray);
	pixmap = pixmap.scaled(ui.labelDeveloper->width(), ui.labelDeveloper->height());
	ui.labelDeveloper->setPixmap(pixmap);

	emit sig_refresh();
}
void CWidgetTask::slot_finish() {
	QSqlQuery sql_query;
	QString strSql;
	strSql = "update tasks set state=:state where id=:id";
	sql_query.prepare(strSql);
	sql_query.bindValue(":state", ETaskState_Finished);// backlog
	sql_query.bindValue(":id", m_nId); // id

	sql_query.exec();	// 插入记录

	emit sig_refresh();
}
void CWidgetTask::slot_back() {

	emit sig_refresh();
}