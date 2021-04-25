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
#pragma once

#include <QAbstractSocket>
#include <QList>
#include <QMutex>
#include <QObject>
#include <QThread>

QT_BEGIN_NAMESPACE
class QTcpServer;
class QTcpSocket;
QT_END_NAMESPACE

class CClientConnection;

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

	/**
	*	@brief 根据id获取数据
	*	@param[in] id 数据的id
	*   @return 数据的id
	*/
	qreal getDataById(qint32 id);
	/**
	*	@brief 设置数据
	*	@param[in] id 数据的id
	*	@param[in] value 数据的值
	*   @return void
	*/
	void setData(qint32 id, qreal value); 
public slots:
	void slot_newConnection();
	void slot_readyToRead();
	void slot_disconnected();
private:
	QTcpServer * m_pTcpServer;
	QList<CClientConnection*> m_clientConnections; /// 客户端连接对象列表
	QMap<qint32, qreal> m_mapData;		/// 数据集
	QMutex m_mtxData;					/// 用来保护数据集的互斥锁
};