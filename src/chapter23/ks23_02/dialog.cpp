/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.cpp
\brief  CDialog
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#include "dialog.h"
#include "qcustomplot.h"

CDialog::CDialog(QWidget* pParent) : QDialog(pParent) {
	ui.setupUi(this);

	initialize();
	connect(ui.btnOk, &QPushButton::clicked, this, &CDialog::accept);
}

CDialog::~CDialog(){
	
}


void CDialog::initialize() {
	ui.plotWidget->addGraph();
	// 设定背景为黑色
	ui.plotWidget->setBackground(QBrush(Qt::gray));
	//设定右上角图例可见
	ui.plotWidget->legend->setVisible(true);
	//设定右上角图例的字体
	ui.plotWidget->legend->setFont(QFont("Helvetica", 9));
	QVector<qreal> x(360), y(360);
	int nData = 0;
	// 为折线添加数据
	for (int i = 0; i<360; i++) {
		x[i] = i;
		y[i] = sin(i/16.f);
		qDebug() << i << "," << y[i];
	}

	//设置画笔
	ui.plotWidget->graph(0)->setPen(QPen(Qt::blue));
	//设置右上角图形标注名称
	ui.plotWidget->graph(0)->setName("curve");
	//传入数据，setData的两个参数类型为double
	ui.plotWidget->graph(0)->setData(x, y);

	//设置X轴文字标注
	ui.plotWidget->xAxis->setLabel("angle");
	ui.plotWidget->xAxis->setTicks(true);
	ui.plotWidget->xAxis->setTickLabels(true);
	//设置Y轴文字标注
	ui.plotWidget->yAxis->setLabel("sin(x)");
	//设置X轴坐标范围
	ui.plotWidget->xAxis->setRange(0, 360);
	//设置Y轴坐标范围
	ui.plotWidget->yAxis->setRange(-1, 1);
	ui.plotWidget->yAxis->setTicks(true);
	//在坐标轴右侧和上方画线，和X/Y轴一起形成一个矩形
	ui.plotWidget->axisRect()->setupFullAxesBox();
}