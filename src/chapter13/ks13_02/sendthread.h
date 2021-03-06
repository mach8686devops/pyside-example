/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: sendthread.h
\brief  CSendThread
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/
#pragma once

#include <QThread>
#include <QMutex>

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

class CSendThread : public QThread {
public:
    CSendThread();
	~CSendThread();

	virtual void run();
    /**
    * @brief	设置事件接收者
    * @return void.
    */
	void setDialog(QWidget* pDialog) {
		m_pDialog = pDialog;
	}
    /**
    * @brief	线程是否正在运行
    * @return true:正在运行, false:线程已终止.
    */
    bool isWorking();
    /**
    * @brief	终止线程运行
    * @return   void
    */
    void exitThread();
private:
    QMutex m_mtxRunning;/// 保护m_bWorking
    bool m_bWorking;	/// 线程正在工作
    bool m_bFinished;	/// 线程已停止工作
	QWidget *m_pDialog; /// 主界面对象
};
