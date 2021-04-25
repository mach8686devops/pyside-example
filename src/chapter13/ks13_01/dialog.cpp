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
#include "recvthread.h"
#include "sendthread.h"

CDialog::CDialog(QWidget* pParent) : QDialog(pParent), m_pRecvThread(new CRecvThread), m_pSendThread(new  CSendThread) {
	ui.setupUi(this);
	
	connect(ui.btnStartThread, SIGNAL(clicked()), this, SLOT(slot_startthread()));
	connect(ui.btnStopThread, SIGNAL(clicked()), this, SLOT(slot_stopthread()));
}

CDialog::~CDialog(){
	slot_stopthread();
}


void CDialog::slot_startthread() {
	m_pRecvThread->start();
	m_pSendThread->start();
}
void CDialog::slot_stopthread() {
	m_pRecvThread->exitThread();
	m_pSendThread->exitThread();
}