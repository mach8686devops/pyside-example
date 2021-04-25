/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: burndown.cpp
\brief  CWidgetBurndown
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#include "burndown.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include "qcustomplot.h"
#include "config.h"
#include "projectinfo.h"

CWidgetBurndown::CWidgetBurndown(QWidget* pParent) : QWidget(pParent), m_nSprintIndex(-1) {
	ui.setupUi(this);

	initialize();
	connect(ui.btnGetback, &QPushButton::clicked, this, &CWidgetBurndown::sig_getBackToSprint);
}

CWidgetBurndown::~CWidgetBurndown(){
	
}

void CWidgetBurndown::clear() {
	ui.label_projectName->setText("");
	ui.label_sprintNo->setText("");
	QVector<qreal> x(0), y(0);
	m_pPlotBurnDown->graph(0)->setData(x, y);
}

void CWidgetBurndown::setSprintInfo(const QString& strProjectCode, int sprintId) {
	clear();
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
	load(m_strProjectCode, m_nSprintIndex);
}
void CWidgetBurndown::initialize() {
	ui.label_projectName->setText("");
	QString strStyleSheet = CConfig::instance().getStyleSheetA();
	QGridLayout* gridLayout_15 = new QGridLayout(ui.widget);
	gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
	m_pPlotBurnDown = new QCustomPlot(ui.widget);
	m_pPlotBurnDown->setObjectName(QStringLiteral("graphicsView_burnDown"));
	QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy1.setHeightForWidth(m_pPlotBurnDown->sizePolicy().hasHeightForWidth());
	m_pPlotBurnDown->setSizePolicy(sizePolicy1);
	m_pPlotBurnDown->setStyleSheet(strStyleSheet);
	gridLayout_15->addWidget(m_pPlotBurnDown, 0, 0, 1, 1);
	//添加图形
	m_pPlotBurnDown->addGraph();
	clear();
}
void CWidgetBurndown::load(const QString& strProjectCode, int sprintId) {
	setBurnDown(m_pPlotBurnDown, strProjectCode, sprintId);

}
void CWidgetBurndown::setBurnDown(QCustomPlot* pCustomPlot, const QString& strProjectCode, int sprintId) {
	int nSprintCycle = CProjectInfo::getSprintCycle(strProjectCode);
	int nSprintDays = nSprintCycle * 5;
	// 获取指定项目当前迭代的燃尽图数据
	QList<QDate> lstDate;
	QList<int> lstData;
	int nCount = CProjectInfo::getBurndownData(strProjectCode, sprintId, lstDate, lstData);
	//设定背景为黑色
	//pCustomPlot->setBackground(QBrush(Qt::black));
	//设定右上角图形标注可见
	pCustomPlot->legend->setVisible(false);
	QVector<qreal> x(nCount), y(nCount);
	QList<int>::iterator iteData = lstData.begin();
	qreal min = 99999;
	qreal max = 0;
	int nData = 0;
	for (int i = 0; i<nCount; i++, iteData++)
	{
		x[i] = i;
		nData = *iteData;
		y[i] = nData;
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

	//设置画笔
	pCustomPlot->graph(0)->setPen(QPen(Qt::blue));
	//设置右上角图形标注名称
	pCustomPlot->graph(0)->setName(tr("burndown curve"));
	//传入数据，setData的两个参数类型为double
	pCustomPlot->graph(0)->setData(x, y);

	//设置X轴文字标注
	pCustomPlot->xAxis->setLabel("date");
	pCustomPlot->xAxis->setTicks(true);
	pCustomPlot->xAxis->setTickLabels(false);
	//设置Y轴文字标注
	pCustomPlot->yAxis->setLabel(tr("workload"));
	//设置X轴坐标范围
	pCustomPlot->xAxis->setRange(0, nSprintDays);
	//设置Y轴坐标范围
	pCustomPlot->yAxis->setRange(min, max);
	pCustomPlot->yAxis->setTicks(true);
	pCustomPlot->yAxis->setTickLabels(true);
	pCustomPlot->legend->setVisible(false); //设置图例是否可用
	//在坐标轴右侧和上方画线，和X/Y轴一起形成一个矩形
	pCustomPlot->axisRect()->setupFullAxesBox();
}