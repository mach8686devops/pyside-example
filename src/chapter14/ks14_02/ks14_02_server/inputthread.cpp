/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: inputthread.cpp
\brief CInputThread
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/4
*/
#include "inputthread.h"
#include <iostream>
#include <QTextStream>

void CInputThread::run() {
	QTextStream qin(stdin, QIODevice::ReadOnly);
	while (true) {
		QString qstr;
		qin >> qstr;
		if (qstr == "exit") {
			exit();
			break;
		}
		else {
			std::cout	<< "if you want to quit, please input:exit"
						<< std::endl;
		}
		QThread::msleep(10);
	}
}