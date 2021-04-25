/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: server.h
\brief CServer
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/8
*/
#include <QApplication>
#pragma once

#include <QObject>

QT_BEGIN_NAMESPACE
class QTcpServer;
QT_END_NAMESPACE

class CServer : public QObject {
	Q_OBJECT
public:
	/**
	* @brief  构造函数
	* @return 无
	*/
	CServer();
	/**
	* @brief  析构函数
	* @return 无
	*/
	~CServer();

	/**
	* @brief  启动监听
	* @return true:成功,false:失败
	*/
	bool startListen();

public slots:
	/**
	* @brief  发送数据给客户端
	* @return void
	*/
	void sendData();
private:
	QTcpServer * m_pTcpServer = nullptr;

};