/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: sprint.cpp
\brief  CWidgetSprint
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#include "sprint.h"
#include <QDate>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSpacerItem>
#include <QList>
#include "customwidget.h"
#include "backlog.h"
#include "task.h"
#include "config.h"

static const int c_startRow = 4;
CWidgetSprint::CWidgetSprint(QWidget* pParent, int id) 
	: QWidget(pParent),
	m_nSprintIndex(id),
	m_nIndex(c_startRow) {
    ui.setupUi(this);
	// 样式
	QString strStyleSheetLeft = CConfig::instance().getStyleSheetLeftDark();
	QString strStyleSheetRight = CConfig::instance().getStyleSheetRightDark();
	QString strStyleSheetBase = CConfig::instance().getStyleSheetBaseDark();
	ui.frame_2->setStyleSheet(strStyleSheetLeft);
	ui.frame_7->setStyleSheet(strStyleSheetBase);
	ui.frame_10->setStyleSheet(strStyleSheetRight);

	ui.label_sprintNo->setText(QString("Sprint:%1").arg(m_nSprintIndex));
	connect(ui.btnAddBacklog, &QPushButton::clicked, this, &CWidgetSprint::slot_addBacklog);
	connect(ui.btnGetback, &QPushButton::clicked, this, &CWidgetSprint::sig_getBack);
	connect(ui.btnFinish, &QPushButton::clicked, this, &CWidgetSprint::slot_finish);
	connect(ui.btnBurndown, &QPushButton::clicked, this, &CWidgetSprint::slot_showBurndown);
}

CWidgetSprint::~CWidgetSprint(){

}

void CWidgetSprint::slot_finish() {
	// 作业: 
	//     根据backlog的完成情况，更新burdown表中本次迭代的燃尽图数据
}
void CWidgetSprint::slot_showBurndown() {
	emit sig_burndown(m_strProjectCode, m_nSprintIndex);
}

void CWidgetSprint::slot_addBacklog(){	
	if (!CConfig::instance().isAuthorized()) {
		QMessageBox::information(this, tr("task"), tr("please login"));
		return;
	}
	QSqlQuery sql_query;
	sql_query.prepare("insert into backlogs(projectcode,sprintid,workloade,workloadr,state) " 
						" values(:projectcode,:sprintid,:workloade,:workloadr,:state)");
	sql_query.bindValue(":projectcode", m_strProjectCode);
	sql_query.bindValue(":sprintid", m_nSprintIndex);
	sql_query.bindValue(":workloade", 1);
	sql_query.bindValue(":workloadr", 1);
	sql_query.bindValue(":state", 1);
	if (sql_query.exec()) {
		qDebug() << sql_query.lastError();
	}
	initialize();
}

void CWidgetSprint::clear(){
	QLayoutItem *pLayoutItem = NULL;
	QWidget* pWidget = NULL;
	for (int r = c_startRow; r < ui.gridLayout->rowCount(); r++) {
		for (int c = 0; c < ui.gridLayout->columnCount(); c++) {
			pLayoutItem = ui.gridLayout->itemAtPosition(r, c);
			if (NULL == pLayoutItem)
				continue;
			pWidget = pLayoutItem->widget();
			if (NULL == pWidget)
				continue;
			ui.gridLayout->removeWidget(pWidget);
			delete pWidget;
		}
	}
}
void CWidgetSprint::initialize() {
	clear();
	
	QSqlQuery sql_query;
	QString strSql = QString("select id from backlogs where projectcode=\'%1\' and sprintid=%2").arg(m_strProjectCode).arg(m_nSprintIndex);
	qDebug() << strSql;
	QList<int> lstValues;
	if (sql_query.exec(strSql)) {
		while (sql_query.next()) {
			lstValues << sql_query.value(0).toInt();
		}
	}
	QList<int>::iterator ite = lstValues.begin();
	while (ite != lstValues.end()) {
		add(*ite);
		ite++;
	}
}
void CWidgetSprint::setSprintInfo(const QString& strProjectCode, int sprintId) {
	m_strProjectCode = strProjectCode;
	m_nSprintIndex = sprintId;
	ui.label_sprintNo->setText(QString("Sprint:%1").arg(m_nSprintIndex));
	{
		QSqlQuery sql_query;
		QString strSql = QString("select name from projects where code=\'%1\'").arg(strProjectCode);
		if (sql_query.exec(strSql)) {
			if (sql_query.next()) {
				QString strName = sql_query.value(0).toString();
				ui.label_projectName->setText(strName);
			}
		}
	}
}
void CWidgetSprint::add(int nBacklogId) {
	QString strBacklogId = QString("%1").arg(nBacklogId);
	QString strBacklog;
	QDate dtStart;
	QDate dtEnd;	
	QString strTask;
	
	QSqlQuery sql_query;
	int nEstimateWorkload = 0;
	QString strSql = QString("select backlog,workloade from backlogs where id=%1").arg(nBacklogId);
	qDebug() << strSql;
	if (sql_query.exec(strSql)) {
		if (sql_query.first()) {
			strBacklog = sql_query.value(0).toString();
			nEstimateWorkload = sql_query.value(1).toInt();
		}
		else {
			return;
		}
	}
	else {
		qDebug() << sql_query.lastError();
		return;
	}

	// 样式
	QString stStyleSheetLeft = CConfig::instance().getStyleSheetLeftDark();
	QString stStyleSheetRight = CConfig::instance().getStyleSheetRightDark();
	QString stStyleSheetBase = CConfig::instance().getStyleSheetBaseDark();
	QString stStyleSheet = CConfig::instance().getStyleSheetB();
	QString str;
	QFont ft;
	ft.setPointSizeF(18);
	// backlog
	CCustomWidget *widgetbase_Backlog = new CCustomWidget(this);
	widgetbase_Backlog->setObjectName(strBacklogId + "_" + QStringLiteral("widgetbase_Backlog"));
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(widgetbase_Backlog->sizePolicy().hasHeightForWidth());
	widgetbase_Backlog->setSizePolicy(sizePolicy);
	widgetbase_Backlog->setMaximumSize(QSize(600, 16667777));
	widgetbase_Backlog->setStyleSheet(stStyleSheetBase);
	QGridLayout* gridLayout_11 = new QGridLayout(widgetbase_Backlog);
	gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
	CWidgetBacklog* backlogText = new CWidgetBacklog(widgetbase_Backlog, m_strProjectCode, nBacklogId, CWidgetTask::ETaskState_Todo);
	backlogText->setEstimateWorkload(nEstimateWorkload);
	backlogText->setBacklog(strBacklog);	
	backlogText->setObjectName(QStringLiteral("backlogText"));
	sizePolicy.setHeightForWidth(backlogText->sizePolicy().hasHeightForWidth());
	backlogText->setSizePolicy(sizePolicy);
	backlogText->setStyleSheet(stStyleSheet);
	gridLayout_11->addWidget(backlogText, 0, 0, 1, 1);
	QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	gridLayout_11->addItem(verticalSpacer, 1, 0, 1, 1);

	ui.gridLayout->addWidget(widgetbase_Backlog, m_nIndex, 0, 1, 1);
	connect(backlogText, &CWidgetBacklog::sig_saved, this, &CWidgetSprint::initialize);
	connect(backlogText, &CWidgetBacklog::sig_taskAdded, this, &CWidgetSprint::initialize);
	// tasks - Doing
	CCustomWidget *widgetbase_Task = new CCustomWidget(this);
	widgetbase_Task->setObjectName(strBacklogId + "_" + QStringLiteral("widgetbase_Task"));
	QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
	sizePolicy1.setHorizontalStretch(0);
	sizePolicy1.setVerticalStretch(0);
	sizePolicy1.setHeightForWidth(widgetbase_Task->sizePolicy().hasHeightForWidth());
	widgetbase_Task->setSizePolicy(sizePolicy1);
	widgetbase_Task->setMaximumSize(QSize(600, 16667777));
	widgetbase_Task->setStyleSheet(stStyleSheetBase);
	QGridLayout* gridLayout_12 = new QGridLayout(widgetbase_Task);
	gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
	ui.gridLayout->addWidget(widgetbase_Task, m_nIndex, 1, 1, 1);

	int nId = 0;
	nEstimateWorkload = 0;
	QString strDeveloper;
	strTask;
	strSql = QString("select id, task, workloade, developer from tasks where projectcode=\'%1\' and backlogid=%2 and  state=%3").
					arg(m_strProjectCode).
					arg(nBacklogId).
					arg(CWidgetTask::ETaskState_Doing);
	qDebug() << strSql;
	int index = 0;
	if (sql_query.exec(strSql)) {
		while (sql_query.next()) {
			nId = sql_query.value(0).toInt();
			strTask = sql_query.value(1).toString();
			nEstimateWorkload = sql_query.value(2).toInt();
			strDeveloper = sql_query.value(3).toString();

			CWidgetTask* taskWidget = new CWidgetTask(widgetbase_Task, CWidgetTask::ETaskState_Doing);
			taskWidget->setId(nId);
			taskWidget->setEstimateWorkload(nEstimateWorkload);
			taskWidget->setTask(strTask);
			taskWidget->setDeveloper(strDeveloper);
			taskWidget->setObjectName(QStringLiteral("taskWidget"));
			taskWidget->setStyleSheet(stStyleSheet);
			gridLayout_12->addWidget(taskWidget, index++, 0, 1, 1);
			connect(taskWidget, &CWidgetTask::sig_refresh, this, &CWidgetSprint::initialize);
		}
		verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
		gridLayout_12->addItem(verticalSpacer, index, 0, 1, 1);
	}

	// tasks - Finished
	CCustomWidget *widgetbase_TaskFinished = new CCustomWidget(this);
	widgetbase_TaskFinished->setObjectName(strBacklogId + "_" + QStringLiteral("widgetbase_TaskFinished"));
	QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
	sizePolicy2.setHorizontalStretch(0);
	sizePolicy2.setVerticalStretch(0);
	sizePolicy2.setHeightForWidth(widgetbase_TaskFinished->sizePolicy().hasHeightForWidth());
	widgetbase_TaskFinished->setSizePolicy(sizePolicy2);
	widgetbase_TaskFinished->setMaximumSize(QSize(600, 16667777));
	widgetbase_TaskFinished->setStyleSheet(stStyleSheetBase);
	QGridLayout* gridLayout_13 = new QGridLayout(widgetbase_TaskFinished);
	gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
	ui.gridLayout->addWidget(widgetbase_TaskFinished, m_nIndex, 2, 1, 1);

	CWidgetBacklog* backlogTextFinished = new CWidgetBacklog(widgetbase_Backlog, m_strProjectCode, nBacklogId, CWidgetTask::ETaskState_Finished);
	backlogTextFinished->setEstimateWorkload(nEstimateWorkload);
	backlogTextFinished->setBacklog(strBacklog);
	backlogTextFinished->setObjectName(QStringLiteral("backlogText"));
	sizePolicy.setHeightForWidth(backlogText->sizePolicy().hasHeightForWidth());
	backlogTextFinished->setSizePolicy(sizePolicy);
	backlogTextFinished->setStyleSheet(stStyleSheet);
	gridLayout_13->addWidget(backlogTextFinished, 0, 0, 1, 1);
	verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	gridLayout_13->addItem(verticalSpacer, 1, 0, 1, 1);

	// 华丽的分割线
	QFrame* line = new QFrame(this);
	line->setObjectName(QStringLiteral("line"));
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	ui.gridLayout->addWidget(line, m_nIndex + 1, 0, 1, 3);
	m_nIndex +=2;
}
