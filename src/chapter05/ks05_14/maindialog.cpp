/*! 
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

CMainDialog::CMainDialog(QWidget* pParent) : QDialog(pParent), m_timerId(0){
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
	// 将图片缩放到指定尺寸
	m_movie->setScaledSize(QSize(300, 300));
	ui.label_gif->setMovie(m_movie);
	m_movie->start();

	m_png[0] = QPixmap(":/images/pic1.png").scaled(400,500);
	m_png[1] = QPixmap(":/images/pic2.png").scaled(400, 500);
	m_png[2] = QPixmap(":/images/pic3.png").scaled(400, 500);
	m_png[3] = QPixmap(":/images/pic4.png").scaled(400, 500);
	ui.label_png->setPixmap(m_png[0]);

    m_timerId = startTimer(300, Qt::PreciseTimer);// 启动定时器，单位:毫秒

    ui.pushButton->setText("stop");

}


void CMainDialog::onStartStop() 
{
	m_bStart = !m_bStart;
	if (m_bStart) {
		ui.pushButton->setText("stop");
        m_timerId = startTimer(300, Qt::PreciseTimer);// 启动定时器，单位:毫秒
 	    m_movie->start(); // 启动gif的动画
	}
	else {		
		ui.pushButton->setText("start");
        // 关闭定时器
        killTimer(m_timerId);
        m_movie->stop(); // 停止gif的动画
	}
}

void CMainDialog::timerEvent(QTimerEvent *event){
    if (m_timerId == event->timerId()) { // 判断是否是我们需要的定时器，这点很重要!
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
}