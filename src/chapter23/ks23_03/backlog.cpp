/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: backlog.cpp
\brief	
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/11 
*/
#include "backlog.h"
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QPointF>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include "config.h"
#include "task.h"

CWidgetBacklog::CWidgetBacklog(QWidget* parent, const QString& strProjectCode, int backlogId, CWidgetTask::ETaskState eState) :
	QFrame(parent),
	m_strProjectCode(strProjectCode),
	m_nEstimateWorkload(0),
	m_nId(backlogId),
	m_eState(eState) {
	ui.setupUi(this);
	initialize();
	connect(ui.btnSave, &QPushButton::clicked, this, &CWidgetBacklog::slot_save);
	connect(ui.btnAddTask, &QPushButton::clicked, this, &CWidgetBacklog::slot_addTask);	
}
void CWidgetBacklog::initialize() {
	if (CWidgetTask::ETaskState_Finished == m_eState) {
		ui.btnSave->hide();
		ui.btnAddTask->hide();
	}
	ui.labelBacklog->setText(tr("backlog:%1").arg(m_nId));

	QString stStyleSheet = CConfig::instance().getStyleSheetB();
	int nId = 0;
	int nEstimateWorkload = 0;
	QString strDeveloper;
	QString strTask;
	QSqlQuery sql_query;
	QString strSql = QString("select id, task, workloade, developer from tasks where projectcode=\'%1\' and backlogid=%2 and state=%3").
		arg(m_strProjectCode).
		arg(m_nId).
		arg(m_eState);
	qDebug() << strSql;
	int index = 0;
	QGridLayout* gridLayout_1 = new QGridLayout(ui.frameTasks);
	gridLayout_1->setObjectName(QStringLiteral("gridLayout_1"));
	if (sql_query.exec(strSql)) {
		while (sql_query.next()) {
			nId = sql_query.value(0).toInt();
			strTask = sql_query.value(1).toString();
			nEstimateWorkload = sql_query.value(2).toInt();
			strDeveloper = sql_query.value(3).toString();

			CWidgetTask* taskWidget = new CWidgetTask(ui.frameTasks, m_eState);
			taskWidget->setId(nId);
			taskWidget->setEstimateWorkload(nEstimateWorkload);
			taskWidget->setTask(strTask);
			taskWidget->setDeveloper(strDeveloper);
			taskWidget->setObjectName(QStringLiteral("taskWidget"));
			taskWidget->setStyleSheet(stStyleSheet);
			gridLayout_1->addWidget(taskWidget, index++, 0, 1, 1);
			connect(taskWidget, &CWidgetTask::sig_refresh, this, &CWidgetBacklog::sig_taskAdded);
		}
	}
}
void CWidgetBacklog::slot_addTask() {
	QString strDeveloper = CConfig::instance().getUser();
	if (strDeveloper.isEmpty()) {
		QMessageBox::information(this, tr("task"), tr("please login"));
		return;
	}
	QSqlQuery sql_query;
	sql_query.prepare("insert into tasks(projectcode,backlogid,developer,workloade,workloadr,state) "
		" values(:projectcode,:backlogid,:developer,:workloade,:workloadr,:state)");
	sql_query.bindValue(":projectcode", m_strProjectCode);
	sql_query.bindValue(":backlogid", m_nId);
	sql_query.bindValue(":developer", "");
	sql_query.bindValue(":workloade", 1);
	sql_query.bindValue(":workloadr", 1);
	sql_query.bindValue(":state", CWidgetTask::ETaskState_Todo);
	if (sql_query.exec()) {
		qDebug() << sql_query.lastError();
	}
	emit sig_taskAdded();
}

void CWidgetBacklog::slot_save() {
	QString strDeveloper = CConfig::instance().getUser();
	if (strDeveloper.isEmpty()) {
		QMessageBox::information(this, tr("task"), tr("please login"));
		return;
	}
	QString strBacklog = ui.pleBacklog->toPlainText();
	m_nEstimateWorkload = ui.leEstimatedWorkload->text().toInt();

	QSqlQuery sql_query;
	QString strSql;
	strSql = "update backlogs set backlog=:backlog, workloade=:workloade where id=:id";
	sql_query.prepare(strSql);
	sql_query.bindValue(":backlog", strBacklog);// backlog
	sql_query.bindValue(":workloade", m_nEstimateWorkload); // 估计工作量
	sql_query.bindValue(":id", m_nId); // id
	
	sql_query.exec();	// 插入记录
	emit sig_saved();
}

void CWidgetBacklog::setEstimateWorkload(int days) {
	m_nEstimateWorkload = days;
	ui.leEstimatedWorkload->setText(QString("%1").arg(days));
}
void CWidgetBacklog::setId(int id) {
	m_nId = id;
	ui.labelBacklog->setText(tr("backlog:%1").arg(id));
}

void CWidgetBacklog::enterEvent(QEvent *event){
	QFrame::enterEvent(event);
	QString str = objectName();
	int idx = str.lastIndexOf("_"); // 找到项目编号
	str = str.left(idx);
	emit sig_enter(str);
}

void CWidgetBacklog::leaveEvent(QEvent *event) {
	QFrame::leaveEvent(event);
	QString str = objectName();
	int idx = str.lastIndexOf("_"); // 找到项目编号
	str = str.left(idx);
	emit sig_leave(str);
}
void CWidgetBacklog::mousePressEvent(QMouseEvent *event) {
	QFrame::mousePressEvent(event);
	QString str = objectName();
	int idx = str.lastIndexOf("_"); // 找到项目编号
	str = str.left(idx);
	emit sig_pressed(str);
}