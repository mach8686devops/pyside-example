/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: textedit.cpp
\brief	
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9 
*/
#include "splashscreen.h"
#include <QProgressBar>

CSplashScreen::CSplashScreen(const QPixmap &pixmap) : 
	QSplashScreen(pixmap) {
	m_pProgressBar = new QProgressBar(this);
	// 设置进度条的位置
	m_pProgressBar->setGeometry(0,						// x
								pixmap.height()-50,		// y
								pixmap.width(),			// width
								30);					// height
	// 设置进度条的样式
	m_pProgressBar->setStyleSheet(
		"QProgressBar {color:black;font:30px;text-align:center; } \
         QProgressBar::chunk {background-color: rgb(200, 160, 16);}");

	// 设置进度条的范围
	m_pProgressBar->setRange(0, 100);

	// 设置进度条的初始值
	m_pProgressBar->setValue(0);
}

void CSplashScreen::setProgress(quint32 value) {
	m_pProgressBar->setValue(value%101);// 使用101=100+1作为模，目的是当value=100时，value%101=100。
}
