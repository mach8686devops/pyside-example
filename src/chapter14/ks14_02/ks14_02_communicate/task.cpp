/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: task.cpp
\brief  CTask
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/4
*/
#include "task.h"

CTask::CTask() {

}
CTask::~CTask() {

}

ETASKTYPE CTask::parseTaskType(QDataStream& inStream) {
	ETASKTYPE taskType = ETASK_INVALID;
	inStream.startTransaction();
	qint32 iVal = -1;
	inStream >> iVal;
	if (!inStream.commitTransaction()) {
		inStream.rollbackTransaction();
		return ETASK_INVALID;
	}
	taskType = static_cast<ETASKTYPE>(iVal);
	return taskType;
}
CTask* CTask::createTask(ETASKTYPE taskType) {
	switch (taskType) {
	case ETASK_HELLO:
		return new CHelloTask;
	case ETASK_SETONEDATA:
		return new CSetOneDataTask;
	case ETASK_GETONEDATA:
		return new CGetOneDataTask;
	case ETASK_ONEDATARETURNED:
		return new COneDataReturnedTask;
	default:
		break;
	}
	return NULL;
}

///////////////////////////////////////////////////////
void CHelloTask::sendFrame(QDataStream& out) {
	qint32 iTaskType = ETASK_HELLO;
	out << iTaskType;
	out << m_str;
}

bool CHelloTask::parseFrame(QDataStream& inStream) {
	inStream.startTransaction();
	inStream >> m_str;
	if (!inStream.commitTransaction()) {
		m_str.clear();
		inStream.rollbackTransaction();
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////
void CSetOneDataTask::sendFrame(QDataStream& out) {
	qint32 iTaskType = taskType();
	out << iTaskType;
	out << m_dataId;
	out << m_dataValue;
}
bool CSetOneDataTask::parseFrame(QDataStream& inStream) {
	inStream.startTransaction();
	inStream >> m_dataId;
	inStream >> m_dataValue;
	if (!inStream.commitTransaction()) {
		m_dataId = 0;
		m_dataValue = 0.f;
		inStream.rollbackTransaction();
		return false;
	}
	return true;
}
