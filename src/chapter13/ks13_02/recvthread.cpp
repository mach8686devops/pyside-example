/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: sendthread.cpp
\brief  CRecvThread 目录扫描线程，负责扫描指定目录并发送事件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/
#include <QFile>
#include <QTextStream>
#include "baseapi.h"
#include "config.h"

#include "recvthread.h"

CRecvThread::CRecvThread() : QThread(), m_bWorking(false), m_bFinished(false) {

}

CRecvThread::~CRecvThread() {

}

void CRecvThread::run()
{
    m_bWorking = true;
    QString strFileName = ns_train::getPath("$TRAINDEVHOME/test/chapter13/ks13_02/recv.txt");
    QFile file(strFileName);
    QString str;
    QStringList strList;
    while (isWorking()) {
		sleep(1);		
        if (!file.open(QFile::ReadOnly | QFile::Text))
            continue;
        QTextStream in(&file);
        in >> str;
        file.close();
        strList = str.split(",");
        if (2 == strList.size()) {
            CConfig::instance().setTeacherNumber(strList[0].toInt());
            CConfig::instance().setStudentNumber(strList[1].toInt());
        }
	}
    m_bFinished = true;
}
bool CRecvThread::isWorking()
{
    QMutexLocker locker(&m_mtxRunning);
    return m_bWorking;
}
void CRecvThread::exitThread()
{
    {
        QMutexLocker locker(&m_mtxRunning);
        m_bWorking = false;
    }
    while (!m_bFinished)
    {
        QThread::msleep(10);
    }
}
