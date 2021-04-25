/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: client.h
\brief CClient类定义头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/
#pragma once

#include "ui_client.h" // 头文件名称来自: client.ui  ---> ui_client.h
#include <QDataStream>
#include <QAbstractSocket>

QT_BEGIN_NAMESPACE
class QTcpSocket;
class QNetworkSession;
QT_END_NAMESPACE
class CClientConnection;
class CClient : public QDialog {
	Q_OBJECT
public:
	/**
	* @brief  构造函数
	* @return 无
	*/
	CClient(QWidget* pParent);
	/**
	* @brief  析构函数
	* @return 无
	*/
	~CClient();
private slots:
	void slot_connectToServer();
	void slot_readyToRead();
	void slot_SetOneData();
	void slot_GetOneData();
	void slot_displayError(QAbstractSocket::SocketError socketError);
	void slot_sessionOpened();
private:
	/**
	* @brief  初始化界面
	* @return 无
	*/
	void setupUi();
	/**
	* @brief  关联信号槽
	* @return 无
	*/
	void connectSignalAndSlots();
	/**
	* @brief  初始化网络任务
	* @return 无
	*/
	void initialSession();
private:
	Ui::CClient ui;
	QTcpSocket *m_pTcpSocket;
	QDataStream m_inStream;
	QNetworkSession *m_pNetworkSession; /// 有些平台需要启动网络任务才能进行正常的网络通信。
	CClientConnection* m_pClientConnection; /// 客户端连接管理对象
};