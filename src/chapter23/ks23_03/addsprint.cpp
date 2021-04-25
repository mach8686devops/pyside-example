/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: addsprint.cpp
\brief  CWidgetAddSprint
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#include "addsprint.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>
#include "user.h"
#include "config.h"

CWidgetAddSprint::CWidgetAddSprint(QWidget* pParent) : QWidget(pParent),m_bModify(false) {
    ui.setupUi(this);
	initialize();
	connect(ui.btnSave, &QPushButton::clicked, this, &CWidgetAddSprint::slot_save);
	connect(ui.btnGetback, &QPushButton::clicked, this, &CWidgetAddSprint::sig_getBack);
}

CWidgetAddSprint::~CWidgetAddSprint() {

}

void CWidgetAddSprint::initialize() {
	
}

void CWidgetAddSprint::clear() {
	ui.leProjectCode->setText("");
	//ui.leProjectName->setText("");
	ui.leCurrentSprint->setText("1");
	ui.leEstimatedWorkload->setText("1");
	ui.dtStart->setDate(QDateTime::currentDateTime().date());
	ui.dtEnd->setDate(QDateTime::currentDateTime().date());
}

void CWidgetAddSprint::slot_save() {
	QString strProjectCode = ui.leProjectCode->text();
	//QString strProjectName = ui.leProjectName->text();
	int nCurrentSprint = ui.leCurrentSprint->text().toInt();
	QDate dtStart = ui.dtStart->date();
	QDate dtEnd = ui.dtEnd->date();
	int nEstimatedWorkload = ui.leEstimatedWorkload->text().toInt();
		
	QSqlQuery sql_query;
	QString strSql;

	sql_query.prepare("insert into sprints (projectcode,id, startdate,enddate,workloade) "
		"values (:projectcode,:id, :startdate,:enddate,:workloade)");
	sql_query.bindValue(":projectcode", strProjectCode);
	sql_query.bindValue(":id", nCurrentSprint);
	sql_query.bindValue(":startdate", dtStart.toString());
	sql_query.bindValue(":enddate", dtEnd.toString());
	sql_query.bindValue(":workloade", nEstimatedWorkload);
	
	sql_query.exec();                   // 插入记录
	qDebug() << sql_query.lastError();
}