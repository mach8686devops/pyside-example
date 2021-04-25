/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: clientconnection.cpp
\brief  CClientConnection
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/4
*/

#include "clientconnection.h"
#include <QtNetwork>
#include <QTcpSocket>
#include "task.h"
/////////////////////////////////////////////////////////////////
CClientConnection::CClientConnection(QTcpSocket* pClientSocket, QObject *parent)
	: QObject(parent)
	, m_pClientSocket(pClientSocket) {

	m_inStream.setDevice(m_pClientSocket);
	m_inStream.setVersion(QDataStream::Qt_5_11);

	m_outSream.setDevice(m_pClientSocket);
	m_outSream.setVersion(QDataStream::Qt_5_11);
}

CClientConnection::~CClientConnection() {
}

void CClientConnection::sendDeal() {
	CTask * pTask = takeOneTask(); // 从任务队列中取出任务
	if (NULL != pTask) {
		pTask->sendFrame(m_outSream); // 将任务组帧并发送
		delete pTask; // 释放内存
	}
}
void CClientConnection::disconnect() {
	if (NULL != m_pClientSocket) {
		m_pClientSocket->disconnectFromHost();
		m_pClientSocket->waitForDisconnected(); // 等待连接断开
	}
}

bool CClientConnection::isSameConnect(const QTcpSocket* pSocket) {
	return (pSocket == m_pClientSocket);
}


void CClientConnection::addTask(CTask* pTask) {
	QMutexLocker locker(&m_mtxTask);
	m_tasks.append(pTask);
}
CTask * CClientConnection::takeOneTask() {
	CTask * pTask = NULL;
	QMutexLocker locker(&m_mtxTask);
	if (m_tasks.size() > 0) {
		pTask = m_tasks[0];		// 取出开头的任务
		m_tasks.removeAt(0);	// 从队列中删除
	}
	return pTask;
}