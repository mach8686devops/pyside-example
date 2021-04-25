/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: logevt.cpp
\brief 日志事项类实现文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9 
*/
#include "logevt.h"
#include <QObject>

CLogEvt::CLogEvt(ELogEvt nType) : QEvent((QEvent::Type)nType) {
}

CLogEvt::~CLogEvt() {
}
SLog CLogEvt::getLog() const {
	return m_log;
}

void CLogEvt::setLog(const SLog& log) {
	m_log = log;
}
////////////////////////////////////////////////////////
QString SLog::translateLevel(ELogLevel level) {
	switch (level)
	{
	case ELogLevel_Error:
		return QObject::tr("Error");
	case ELogLevel_Warning:
		return QObject::tr("Warning");
	case ELogLevel_Normal:
		return QObject::tr("Normal");
	default:
		break;
	}

	return QString::null;
}