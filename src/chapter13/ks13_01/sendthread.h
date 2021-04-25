/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: sendthread.h
\brief 发送数据线程类定义
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/3
* 
*/
#pragma once

#include <QMutex>
#include <QThread>

class CSendThread : public QThread {
public:
    /**
    * @brief  构造函数。
    * @return 无
    */
	CSendThread();
    /**
    * @brief  析构造函数。
    * @return 无
    */
    ~CSendThread();
    /**
    * @brief  线程主循环函数。
    * @return 无
    */
	virtual void run();
	/**
	* @brief 线程是否正在运行
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
};

