/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: projects.cpp
\brief  CWidgetProjects
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#include "projects.h"
#include <QDate>
#include <QGridLayout>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "projectinfo.h"
#include "custombar.h"
#include "customlabel.h"
#include "customwidget.h"
#include "config.h"
#include "qcustomplot.h"
#include "task.h"


CWidgetProjects::CWidgetProjects(QWidget* pParent) : 
	QWidget(pParent),
	m_nProjectIndex(3) {
    ui.setupUi(this);

	// 样式
	QString strStyleSheetLeft = CConfig::instance().getStyleSheetLeftDark();
	QString strStyleSheetRight = CConfig::instance().getStyleSheetRightDark();
	QString strStyleSheetBase = CConfig::instance().getStyleSheetBaseDark();
	ui.frame_ProjectName->setStyleSheet(strStyleSheetLeft);
	ui.frame_timeProgress->setStyleSheet(strStyleSheetBase);
	ui.frame_workloadProgress->setStyleSheet(strStyleSheetBase);
	ui.frame_sprintCycle->setStyleSheet(strStyleSheetBase);
	ui.frame_burnDownChart->setStyleSheet(strStyleSheetRight);

	// 华丽的分割线
	QFrame* line = new QFrame(this);
	line->setObjectName(QStringLiteral("line"));
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	ui.gridLayout->addWidget(line, 2, 0, 1, 5);

	QStringList strList = CProjectInfo::getProjects();
	QStringList::iterator ite = strList.begin();
	while (ite != strList.end()) {
		add(*ite);
		ite++;
	}
}

CWidgetProjects::~CWidgetProjects(){

}

int CWidgetProjects::getFinishedWorkload(const QString& strProjectCode) {
	int finishedWorkLoad = 0;
	QSqlQuery sql_query;
	QString strSql;
	strSql = "select workloadfinished from projects where code='";
	strSql += strProjectCode;
	strSql += "\'";
	qDebug() << strSql;
	if (sql_query.exec(strSql)) {
		if (sql_query.first()) {
			finishedWorkLoad += sql_query.value(0).toInt();
		}
	}
	return finishedWorkLoad;
}
void CWidgetProjects::add(const QString& strProjectCode) {
 	QString strProjectName;
	QDate dtStart;
	QDate dtEnd;
	int nEstimatedWorkload;
	int finishedWorkLoad = getFinishedWorkload(strProjectCode);
	QString strProductOwner;
	QString strScrumMaster;
	QString strTester;
	int nSprintCycle = 1;
	QString strDevelopTeam;
	QStringList strList;
	
	QString strName;
	QSqlQuery sql_query;
	QString strSql;
	strSql = "select name,startdate,enddate,sprintcycle,workloade,po,sm,tester,devteam from projects where code='";
	strSql += strProjectCode;
	strSql += "\'";
	qDebug() << strSql;
	if (sql_query.exec(strSql)) {
		if (sql_query.first()) {
			strProjectName = sql_query.value(0).toString();
			dtStart = QDate::fromString(sql_query.value(1).toString());
			dtEnd = QDate::fromString(sql_query.value(2).toString());
			nSprintCycle = sql_query.value(3).toInt();
			nEstimatedWorkload = sql_query.value(4).toInt();
			strProductOwner = sql_query.value(5).toString();
			strScrumMaster = sql_query.value(6).toString();
			strTester = sql_query.value(7).toString();
			strDevelopTeam = sql_query.value(8).toString();
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
    QString strStyleSheetLeft = CConfig::instance().getStyleSheetLeft();
    QString strStyleSheetRight = CConfig::instance().getStyleSheetRight();
    QString strStyleSheetBase = CConfig::instance().getStyleSheetBase();
    QString strStyleSheet = CConfig::instance().getStyleSheetA();
	QString str;
	QFont ft;
	ft.setPointSizeF(18);
	// 项目名称
	CCustomWidget *widgetbase_ProjectName = new CCustomWidget(this);
    widgetbase_ProjectName->setObjectName(strProjectCode +"_" + QStringLiteral("widgetbaseProjectName"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(widgetbase_ProjectName->sizePolicy().hasHeightForWidth());
    widgetbase_ProjectName->setSizePolicy(sizePolicy);
    widgetbase_ProjectName->setMaximumSize(QSize(16777215, 100));
    widgetbase_ProjectName->setStyleSheet(strStyleSheetLeft);
    QGridLayout* gridLayout_11 = new QGridLayout(widgetbase_ProjectName);
    gridLayout_11->setObjectName(strProjectCode + "_" + QStringLiteral("gridLayout11"));
	CCustomLabel* projectName = new CCustomLabel(widgetbase_ProjectName);
	projectName->setText(strProjectName);
	projectName->setObjectName(strProjectCode + "_" + QStringLiteral("projectName"));
    sizePolicy.setHeightForWidth(projectName->sizePolicy().hasHeightForWidth());
	projectName->setSizePolicy(sizePolicy);
	projectName->setStyleSheet(strStyleSheet);
	projectName->setAlignment(Qt::AlignCenter);
	projectName->setFont(ft);
    gridLayout_11->addWidget(projectName, 0, 0, 1, 1);
    ui.gridLayout->addWidget(widgetbase_ProjectName, m_nProjectIndex, 0, 1, 1);
	connect(widgetbase_ProjectName, &CCustomWidget::sig_enter, this, &CWidgetProjects::slot_enterProject);
	connect(widgetbase_ProjectName, &CCustomWidget::sig_leave, this, &CWidgetProjects::slot_leaveProject);
	connect(widgetbase_ProjectName, &CCustomWidget::sig_pressed, this, &CWidgetProjects::sig_pressed);
	connect(projectName, &CCustomLabel::sig_pressed, this, &CWidgetProjects::sig_pressed);
    // 项目的时间进度
	CCustomWidget* widgetbase_timeProgress = new CCustomWidget(this);
    widgetbase_timeProgress->setObjectName(strProjectCode + "_" + QStringLiteral("widgetbasetimeProgress"));
    widgetbase_timeProgress->setMaximumSize(QSize(150, 16777215));
    widgetbase_timeProgress->setStyleSheet(strStyleSheetBase);
    QGridLayout* gridLayout_12 = new QGridLayout(widgetbase_timeProgress);
    gridLayout_12->setObjectName(strProjectCode + "_" + QStringLiteral("gridLayout12"));
    gridLayout_12->setHorizontalSpacing(7);
	CCustomLabel* projectStartDate = new CCustomLabel(widgetbase_timeProgress);
    projectStartDate->setObjectName(strProjectCode + "_" + QStringLiteral("projectStartDate"));
    projectStartDate->setMaximumSize(QSize(80, 30));
    projectStartDate->setStyleSheet(strStyleSheet);
	str.sprintf("%4d/%d", dtStart.year(), dtStart.month());
	projectStartDate->setText(str);
    gridLayout_12->addWidget(projectStartDate, 0, 0, 1, 1);
	connect(widgetbase_timeProgress, &CCustomWidget::sig_enter, this, &CWidgetProjects::slot_enterProject);
	connect(widgetbase_timeProgress, &CCustomWidget::sig_leave, this, &CWidgetProjects::slot_leaveProject);
	connect(widgetbase_timeProgress, &CCustomWidget::sig_pressed, this, &CWidgetProjects::sig_pressed);
	connect(projectStartDate, &CCustomLabel::sig_pressed, this, &CWidgetProjects::sig_pressed);

	CCustomLabel* projectEndDate = new CCustomLabel(widgetbase_timeProgress);
    projectEndDate->setObjectName(strProjectCode + "_" + QStringLiteral("projectEndDate"));
    projectEndDate->setMaximumSize(QSize(80, 16777215));
    projectEndDate->setStyleSheet(strStyleSheet);
 	str.sprintf("%4d/%d", dtEnd.year(), dtEnd.month());
	projectEndDate->setText(str);
	gridLayout_12->addWidget(projectEndDate, 0, 1, 1, 1);
	connect(projectEndDate, &CCustomLabel::sig_pressed, this, &CWidgetProjects::sig_pressed);

	CCustomBar* graphicsView_timeProgress = new CCustomBar(widgetbase_timeProgress);
    graphicsView_timeProgress->setObjectName(strProjectCode + "_" + QStringLiteral("graphicsViewtimeProgress"));
    sizePolicy.setHeightForWidth(graphicsView_timeProgress->sizePolicy().hasHeightForWidth());
    graphicsView_timeProgress->setSizePolicy(sizePolicy);
    graphicsView_timeProgress->setMaximumSize(QSize(150, 30));
    graphicsView_timeProgress->setStyleSheet(strStyleSheet);
    gridLayout_12->addWidget(graphicsView_timeProgress, 1, 0, 1, 2);
    ui.gridLayout->addWidget(widgetbase_timeProgress, m_nProjectIndex, 1, 1, 1);	
	QDate dtNow = QDate::currentDate();
	graphicsView_timeProgress->setValue(0, dtStart.daysTo(dtEnd), dtStart.daysTo(dtNow));
    // 项目的工作量进度
	CCustomWidget* widgetbase_workloadProgress = new CCustomWidget(this);
    widgetbase_workloadProgress->setObjectName(strProjectCode + "_" + QStringLiteral("widgetbaseworkloadProgress"));
	QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy1.setHeightForWidth(widgetbase_workloadProgress->sizePolicy().hasHeightForWidth());
    widgetbase_workloadProgress->setSizePolicy(sizePolicy1);
    widgetbase_workloadProgress->setMaximumSize(QSize(300, 16777215));
    widgetbase_workloadProgress->setStyleSheet(strStyleSheetBase);
    QGridLayout* gridLayout_13 = new QGridLayout(widgetbase_workloadProgress);
    gridLayout_13->setObjectName(strProjectCode + "_" + QStringLiteral("gridLayout13"));
	CCustomLabel* workloadProgress = new CCustomLabel(widgetbase_workloadProgress);
    workloadProgress->setObjectName(strProjectCode + "_" + QStringLiteral("workloadProgress"));
    workloadProgress->setMinimumSize(QSize(0, 0));
    workloadProgress->setMaximumSize(QSize(300, 30));
  	str = tr("Estimated:%1man-day,finished:%2").arg(nEstimatedWorkload).arg(finishedWorkLoad);
	workloadProgress->setText(str);
	workloadProgress->setStyleSheet(strStyleSheet);
    gridLayout_13->addWidget(workloadProgress, 0, 0, 1, 1);
	// 项目的工作量图示
	CCustomBar* graphicsView_workloadProgress = new CCustomBar(widgetbase_workloadProgress);
    graphicsView_workloadProgress->setObjectName(strProjectCode + "_" + QStringLiteral("graphicsViewworkloadProgress"));
    sizePolicy.setHeightForWidth(graphicsView_workloadProgress->sizePolicy().hasHeightForWidth());
    graphicsView_workloadProgress->setSizePolicy(sizePolicy);
    graphicsView_workloadProgress->setMaximumSize(QSize(16777215, 30));
    graphicsView_workloadProgress->setStyleSheet(strStyleSheet);
    gridLayout_13->addWidget(graphicsView_workloadProgress, 1, 0, 1, 1);
    ui.gridLayout->addWidget(widgetbase_workloadProgress, m_nProjectIndex, 2, 1, 1);
	graphicsView_workloadProgress->setValue(0, nEstimatedWorkload, finishedWorkLoad);
	connect(widgetbase_workloadProgress, &CCustomWidget::sig_enter, this, &CWidgetProjects::slot_enterProject);
	connect(widgetbase_workloadProgress, &CCustomWidget::sig_leave, this, &CWidgetProjects::slot_leaveProject);
	connect(widgetbase_workloadProgress, &CCustomWidget::sig_pressed, this, &CWidgetProjects::sig_pressed);

	// 项目迭代周期
	CCustomWidget* widgetbase_sprintCycle = new CCustomWidget(this);
    widgetbase_sprintCycle->setObjectName(strProjectCode + "_" + QStringLiteral("widgetbasesprintCycle"));
    widgetbase_sprintCycle->setStyleSheet(strStyleSheetBase);
    QGridLayout* gridLayout_14 = new QGridLayout(widgetbase_sprintCycle);
    gridLayout_14->setObjectName(strProjectCode + "_" + QStringLiteral("gridLayout14"));
	CCustomLabel* sprintCycle = new CCustomLabel(widgetbase_sprintCycle);
	sprintCycle->setObjectName(strProjectCode + "_" + QStringLiteral("sprintCycle"));
	sprintCycle->setStyleSheet(strStyleSheet);
	sprintCycle->setAlignment(Qt::AlignCenter);
	sprintCycle->setText(QString("%1Weeks").arg(nSprintCycle));
    gridLayout_14->addWidget(sprintCycle, 0, 0, 1, 1);
    ui.gridLayout->addWidget(widgetbase_sprintCycle, m_nProjectIndex, 3, 1, 1);
	connect(widgetbase_sprintCycle, &CCustomWidget::sig_enter, this, &CWidgetProjects::slot_enterProject);
	connect(widgetbase_sprintCycle, &CCustomWidget::sig_leave, this, &CWidgetProjects::slot_leaveProject);

    // 项目燃尽图
	CCustomWidget* widgetbase_burnDownChart = new CCustomWidget(this);
    widgetbase_burnDownChart->setObjectName(strProjectCode + "_" + QStringLiteral("widgetbaseburnDownChart"));
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(widgetbase_burnDownChart->sizePolicy().hasHeightForWidth());
    widgetbase_burnDownChart->setSizePolicy(sizePolicy1);
    widgetbase_burnDownChart->setMaximumSize(QSize(100, 100));
    widgetbase_burnDownChart->setStyleSheet(strStyleSheetRight);
    QGridLayout* gridLayout_15 = new QGridLayout(widgetbase_burnDownChart);
    gridLayout_15->setObjectName(strProjectCode + "_" + QStringLiteral("gridLayout15"));
	QCustomPlot* pPlot_burnDown = new QCustomPlot(widgetbase_burnDownChart);
	pPlot_burnDown->setObjectName(strProjectCode + "_" + QStringLiteral("plotburnDown"));
    sizePolicy1.setHeightForWidth(pPlot_burnDown->sizePolicy().hasHeightForWidth());
	pPlot_burnDown->setSizePolicy(sizePolicy1);
	pPlot_burnDown->setStyleSheet(strStyleSheet);
    gridLayout_15->addWidget(pPlot_burnDown, 0, 0, 1, 1);
    ui.gridLayout->addWidget(widgetbase_burnDownChart, m_nProjectIndex, 4, 1, 1);
	setBurnDown(pPlot_burnDown, strProjectCode, nSprintCycle);
	connect(widgetbase_burnDownChart, &CCustomWidget::sig_enter, this, &CWidgetProjects::slot_enterProject);
	connect(widgetbase_burnDownChart, &CCustomWidget::sig_leave, this, &CWidgetProjects::slot_leaveProject);
	connect(widgetbase_burnDownChart, &CCustomWidget::sig_pressed, this, &CWidgetProjects::sig_pressed);

	// 华丽的分割线
    QFrame* line = new QFrame(this);
    line->setObjectName(strProjectCode + "_" + QStringLiteral("line"));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    ui.gridLayout->addWidget(line, m_nProjectIndex + 1, 0, 1, 5);
	m_nProjectIndex += 2;
}

void CWidgetProjects::slot_enterProject(const QString& strProjectCode) {
	QString strStyleSheetLeft = CConfig::instance().getStyleSheetLeftDark();
	QString strStyleSheetRight = CConfig::instance().getStyleSheetRightDark();
	QString strStyleSheetBase = CConfig::instance().getStyleSheetBaseDark();
	QObjectList objList = children();
	QString strName;
	QWidget* pWidget = NULL;
	QObjectList::iterator ite = objList.begin();
	for (; ite != objList.end(); ite++) {
		strName = (*ite)->objectName();
		if (strName.indexOf(strProjectCode) == 0) {
			pWidget = dynamic_cast<QWidget*>(*ite);
			if (NULL != pWidget) {
				if (strName.contains("widgetbaseProjectName")) {
					pWidget->setStyleSheet(strStyleSheetLeft);
				}
				else if (strName.contains("widgetbase_burnDownChart")) {
					pWidget->setStyleSheet(strStyleSheetRight);
				}
				else {
					pWidget->setStyleSheet(strStyleSheetBase);
				}
			}
		}
	}
}

void CWidgetProjects::setBurnDown(QCustomPlot* pCustomPlot, const QString& strProjectCode, int nSprintCycle) {
	// 获取指定项目的当前迭代
	int currentSprint = CProjectInfo::getCurrentSprint(strProjectCode);
	// 获取指定项目当前迭代的燃尽图数据
	QList<QDate> lstDate;
	QList<int> lstData;	
	int nCount = CProjectInfo::getBurndownData(strProjectCode, currentSprint, lstDate, lstData);
	int nSprintDays = nSprintCycle * 5;
	QVector<qreal> x(nCount), y(nCount);
	QList<int>::iterator iteData = lstData.begin();
	qreal min = 99999;
	qreal max = 0;
	for (int i = 0; i<nCount; i++, iteData++) {
		x[i] = i;
		y[i] = *iteData;
		if (y[i] > max) {
			max = y[i];
		}
		if (y[i] < min) {
			min = y[i];
		}
	}
	if (min > 0) {
		min = 0;
	}		
	max += 5;
	// 添加图形
	pCustomPlot->addGraph();
	// 设置画笔
	pCustomPlot->graph(0)->setPen(QPen(Qt::blue));
	// 传入数据，setData的两个参数类型为double
	pCustomPlot->graph(0)->setData(x, y);

	pCustomPlot->xAxis->setTicks(false);
	pCustomPlot->xAxis->setTickLabels(false);
	// 设置X轴坐标范围
	pCustomPlot->xAxis->setRange(0, nSprintDays);
	// 设置Y轴坐标范围
	pCustomPlot->yAxis->setRange(min, max);
	pCustomPlot->yAxis->setTicks(false);
	pCustomPlot->yAxis->setTickLabels(false);
	pCustomPlot->legend->setVisible(false); //设置图例是否可用
	// 在坐标轴右侧和上方画线，和X/Y轴一起形成一个矩形
	pCustomPlot->axisRect()->setupFullAxesBox();
}

void CWidgetProjects::slot_leaveProject(const QString& strProjectCode)
{
	QString strStyleSheetLeft = CConfig::instance().getStyleSheetLeft();
	QString strStyleSheetRight = CConfig::instance().getStyleSheetRight();
	QString strStyleSheetBase = CConfig::instance().getStyleSheetBase();
	QObjectList objList = children();
	QString strName;
	QWidget* pWidget = NULL;
	QObjectList::iterator ite = objList.begin();
	for (; ite != objList.end(); ite++) {
		strName = (*ite)->objectName();
		if (strName.indexOf(strProjectCode) == 0) {
			pWidget = dynamic_cast<QWidget*>(*ite);
			if (NULL != pWidget) {
				if (NULL != pWidget) {
					if (strName.contains("widgetbaseProjectName")){
						pWidget->setStyleSheet(strStyleSheetLeft);
					}
					else if (strName.contains("widgetbase_burnDownChart")){
						pWidget->setStyleSheet(strStyleSheetRight);
					}
					else {
						pWidget->setStyleSheet(strStyleSheetBase);
					}
				}
			}
		}
	}
}
