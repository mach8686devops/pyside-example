/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: projectinfo.cpp
\brief  CProjectInfo
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#include "projectinfo.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "user.h"
#include "config.h"

CProjectInfo::CProjectInfo(QWidget* pParent) : QWidget(pParent), m_bModify(false) {
	ui.setupUi(this);

	initialize();
	connect(ui.btnSave, &QPushButton::clicked, this, &CProjectInfo::slot_save);
	connect(ui.btnGetback, &QPushButton::clicked, this, &CProjectInfo::sig_getBack);
}

CProjectInfo::~CProjectInfo() {

}

void CProjectInfo::setModifyMode(bool b) {
	m_bModify = b;
	if (b) {
		ui.btnSave->setText(tr("save"));
	}
	else {
		ui.btnSave->setText(tr("add"));
	}
}
void CProjectInfo::initialize() {
	QStringList strList = CWidgetUser::getUsers();
	QStringList::iterator ite = strList.begin();
	while (ite != strList.end()) {
		ui.cbProductOwner->addItem(*ite);
		ui.cbScrumMaster->addItem(*ite);
		ui.cbTest->addItem(*ite);
		ite++;
	}
}
QStringList CProjectInfo::getProjects() {
	QStringList strList;
	QString strName;
	QSqlQuery sql_query;
	QString strSql;
	strSql = "select code from projects";
	if (sql_query.exec(strSql)) {
		while (sql_query.next()) {
			strName = sql_query.value(0).toString();
			strList << strName;
		}
	}
	else {
		qDebug() << sql_query.lastError();
	}

	return strList;
}

int CProjectInfo::getCurrentSprint(const QString& strProjectCode) {
	int nCurrentSprint = 0;
	QSqlQuery sql_query;
	QString strSql;
	strSql = "select currentsprint from projects where code = \'";
	strSql += strProjectCode;
	strSql += "\'";
	qDebug() << strSql;
	if (sql_query.exec(strSql)) {
		if (sql_query.first()) {
			nCurrentSprint = sql_query.value(0).toInt();
		}
	}
	else {
		qDebug() << sql_query.lastError();
	}
	return nCurrentSprint;
}
int CProjectInfo::getSprintCycle(const QString& strProjectCode) {
	int nSprintCycle = 0;
	QSqlQuery sql_query;
	QString strSql;
	strSql = "select sprintcycle from projects where code = \'";
	strSql += strProjectCode;
	strSql += "\'";
	qDebug() << strSql;
	if (sql_query.exec(strSql)) {
		if (sql_query.first()) {
			nSprintCycle = sql_query.value(0).toInt();
		}
	}
	else {
		qDebug() << sql_query.lastError();
	}
	return nSprintCycle;
}


int CProjectInfo::getBurndownData(const QString& strProjectCode, 
									int sprintId, 
									QList<QDate>& lstDate, 
									QList<int>& lstData) {
	QSqlQuery sql_query;
	QString strSql;
	strSql = "select date,workload from burndown where projectcode = \'";
	strSql += strProjectCode;
	strSql += "\' and sprintid=";
	strSql += QString("%1").arg(sprintId);
	strSql += " order by date";
	qDebug() << strSql;
	int nData = 0;
	if (sql_query.exec(strSql)) {
		while (sql_query.next()) {
			lstDate << sql_query.value(0).toDate();
			nData = sql_query.value(1).toInt();
			lstData << nData; 
			qDebug() << *lstData.begin();
		}
	}
	else {
		qDebug() << sql_query.lastError();
	}
	return int(lstDate.size());
}

void CProjectInfo::clear() {
	ui.leProjectCode->setText("");
	ui.leProjectName->setText("");
	ui.dtStart;
	ui.dtEnd;
	ui.leEstimatedWorkload->setText("1");
	ui.cbProductOwner->setCurrentIndex(-1);
	ui.cbScrumMaster->setCurrentIndex(-1);
	ui.cbTest->setCurrentIndex(-1);
	ui.spinBoxSprintCycle->setValue(2);
	ui.leDevelopTeam->setText("");
}

void CProjectInfo::load(const QString& /*strProjectCode*/) {

}

void CProjectInfo::slot_save() {

	QString strProjectCode = ui.leProjectCode->text();
	QString strProjectName = ui.leProjectName->text();
	QDate dtStart = ui.dtStart->date();
	QDate dtEnd = ui.dtEnd->date();
	int nEstimatedWorkload = ui.leEstimatedWorkload->text().toInt();
	int nCurrentSprint = ui.leCurrentSprint->text().toInt();
	QString strProductOwner = ui.cbProductOwner->currentText();
	QString strScrumMaster = ui.cbScrumMaster->currentText();
	QString strTester = ui.cbTest->currentText();
	int nSprintCycle = ui.spinBoxSprintCycle->value();
	QString strDevelopTeam = ui.leDevelopTeam->text();

	QSqlQuery sql_query;

	QString strSql = "select name from projects where code=\'";
	strSql += strProjectCode;
	strSql += "\'";
	m_bModify = false;
	if (sql_query.exec(strSql)) {
		if (sql_query.first()) {
			m_bModify = true;
		}
	}
	if (m_bModify)
	{
		sql_query.prepare("update projects set name=:name,startdate=:startdate,enddate=:enddate,currentsprint=:currentsprint,sprintcycle=:sprintcycle,workloade=:workloade,po=:po,sm=:sm,tester=:tester,devteam=:devteam where code=:code");
		sql_query.bindValue(":name", strProjectName);
		sql_query.bindValue(":startdate", dtStart.toString());
		sql_query.bindValue(":enddate", dtEnd.toString());
		sql_query.bindValue(":currentsprint", nCurrentSprint);
		sql_query.bindValue(":sprintcycle", nSprintCycle);
		sql_query.bindValue(":workloade", nEstimatedWorkload);
		sql_query.bindValue(":po", strProductOwner);
		sql_query.bindValue(":sm", strScrumMaster);
		sql_query.bindValue(":tester", strTester);
		sql_query.bindValue(":devteam", strDevelopTeam);
		sql_query.bindValue(":code", strProjectCode);
	}
	else {
		sql_query.prepare("insert into projects (name,code,startdate,enddate,currentsprint,sprintcycle,workloade,po,sm,tester,devteam) "
			"values (:name,:code,:startdate,:enddate,:currentsprint,:sprintcycle,:workloade,:po,:sm,:tester,:devteam)");
		sql_query.bindValue(":name", strProjectName);
		sql_query.bindValue(":code", strProjectCode);
		sql_query.bindValue(":startdate", dtStart.toString());
		sql_query.bindValue(":enddate", dtEnd.toString());
		sql_query.bindValue(":currentsprint", 1);
		sql_query.bindValue(":sprintcycle", nSprintCycle);
		sql_query.bindValue(":workloade", nEstimatedWorkload);
		sql_query.bindValue(":po", strProductOwner);
		sql_query.bindValue(":sm", strScrumMaster);
		sql_query.bindValue(":tester", strTester);
		sql_query.bindValue(":devteam", strDevelopTeam);
	}
	sql_query.exec();                   // 插入记录
	qDebug() << sql_query.lastError();
}