﻿/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: maindialog.cpp
\brief  CMainDialog
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#include "maindialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QMovie>
#include <QPushButton>
#include <QTime>
#include <QTimer>

CMainDialog::CMainDialog(QWidget* pParent) : QDialog(pParent), m_pTimer(NULL){
	ui.setupUi(this);
	initialDialog();
}

CMainDialog::~CMainDialog(){
	
}
void CMainDialog::initialDialog() {
	
	m_idx = 0;
	m_bStart = true;

	connect(ui.pushButton, &QPushButton::toggled, this, &CMainDialog::onStartStop);

	QString imgStr(":/images/rainman.gif");
	m_movie = new QMovie(imgStr);
	m_movie->setScaledSize(QSize(400, 500));
	ui.label_gif->setMovie(m_movie);
	m_movie->start();

	m_png[0] = QPixmap(":/images/pic1.png").scaled(400,500);
	m_png[1] = QPixmap(":/images/pic2.png").scaled(400, 500);
	m_png[2] = QPixmap(":/images/pic3.png").scaled(400, 500);
	m_png[3] = QPixmap(":/images/pic4.png").scaled(400, 500);
	ui.label_png->setPixmap(m_png[0]);

    m_pTimer = new QTimer(this);
    connect(m_pTimer, &QTimer::timeout, this, &CMainDialog::slot_timeOut); // 绑定槽函数
    m_pTimer->setInterval(300); // 设置定时器周期。单位:毫秒
    m_pTimer->start(); // 启动定时器
}


void CMainDialog::onStartStop() {
	m_bStart = !m_bStart;
	m_bStart ? (m_pTimer->start(),m_movie->start(),ui.pushButton->setText("stop")) : (m_pTimer->stop(), m_movie->stop(), ui.pushButton->setText("start"));
}

void CMainDialog::slot_timeOut() {
    QTime tm = QTime::currentTime();
    QString str;
    str.sprintf("%02d:%02d:%02d", tm.hour(), tm.minute(), tm.second());
    ui.label->setText(str);

    // 更新图片
    ui.label_png->setPixmap(m_png[m_idx++]);
    if (m_idx > 3) {
        m_idx = 0;
    }
}