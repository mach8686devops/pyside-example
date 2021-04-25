/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: task.h
\brief  CTask
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/
#pragma once

#include "ks14_02.h"
#include <QByteArray>
#include <QDataStream>
#include <QString>

enum ETASKTYPE {
	ETASK_INVALID = -1, /// 无效
	ETASK_HELLO = 1,    /// hello
	ETASK_SETONEDATA,   /// 设置一个数据
	ETASK_GETONEDATA,   /// 获取一个数据
	ETASK_ONEDATARETURNED,/// 返回一个数据
	ETASK_SETDATAS,     /// 设置一批数据
	ETASK_GETDATAS,     /// 获取一批数据
	ETASK_MAX            /// 任务类型的最大值
};

class KS14_02_API CTask {
public:
	CTask();
	virtual ~CTask();

	/**
	*	@brief 任务类型。
	*   @return 任务类型。
	*/
	virtual ETASKTYPE taskType() = 0;
	/**
	*	@brief 组帧并发送。
	*	@param[in|out] ds 输出数据流
	*   @return void
	*/
	virtual void sendFrame(QDataStream& ds) = 0;
	/**
	*	@brief 解帧。
	*	@param[in|out] ds 输入数据流对象
	*   @return true:成功，false:失败
	*/
	virtual bool parseFrame(QDataStream& ds) = 0;

	/**
	*	@brief 从输入数据流获取任务类型。
	*	@param[in|out] ds 输入数据流对象
	*   @return 任务类型。
	*/
	static ETASKTYPE parseTaskType(QDataStream& ds);

	/**
	*	@brief 根据任务类型生成任务对象。
	*          调用者负责销毁任务对象。
	*	@param[in] taskType 任务类型
	*   @return 任务对象
	*/
	static CTask* createTask(ETASKTYPE taskType);
};

class KS14_02_API CHelloTask : public CTask {
public:
	CHelloTask() : CTask(), m_str("I'm Server.Hello!") {}
	virtual ~CHelloTask() {}
	virtual ETASKTYPE taskType() override { return ETASK_HELLO; }

	/**
	*	@brief 把待发送数据进行组帧并发送
	*	@param[out] outBlock 字节流对象
	*   @return void
	*/
	virtual void sendFrame(QDataStream&) override;
	/**
	*	@brief 对接收到的数据进行解帧
	*	@param[in|out] inStream 接收到的数据
	*   @return true:成功, false:失败
	*/
	virtual bool parseFrame(QDataStream& inStream) override;

	/**
	*	@brief 获取本任务的信息
	*	@param[in|out] inBlock 接收到的数据
	*   @return void
	*/
	QString getString() { return m_str; }
	/**
	*	@brief 设置本任务的信息
	*	@param[in] str 本任务的信息
	*   @return void
	*/
	void setString(const QString& str) { m_str = str; }

private:
	QString  m_str;
};
// 向服务端设置一个数据
class KS14_02_API CSetOneDataTask : public CTask {
public:
	CSetOneDataTask() : CTask(), m_dataId(-1), m_dataValue(0.f) {}
	virtual ~CSetOneDataTask() override {}
	virtual ETASKTYPE taskType() override { return ETASK_SETONEDATA; }

	/**
	*	@brief 把待发送数据进行组帧并发送
	*	@param[out] outBlock 字节流对象
	*   @return void
	*/
	virtual void sendFrame(QDataStream&) override;
	/**
	*	@brief 对接收到的数据进行解帧
	*	@param[in|out] inStream 接收到的数据
	*   @return true:成功, false:失败
	*/
	virtual bool parseFrame(QDataStream& inStream) override;

	/**
	*	@brief 获取数据的id
	*   @return 数据的id
	*/
	qint32 getDataId() { return m_dataId; }
	/**
	*	@brief 设置数据的id
	*	@param[in] id 数据的id
	*   @return void
	*/
	void setDataId(qint32 id) { m_dataId = id; }
	/**
	*	@brief 获取数据的值
	*   @return 数据的值
	*/
	qreal getDataValue() { return m_dataValue; }
	/**
	*	@brief 设置数据的值
	*	@param[in] val 数据的值
	*   @return void
	*/
	void setDataValue(qreal val) { m_dataValue = val; }

private:
	qint32  m_dataId;
	qreal   m_dataValue;
};
// 从服务端获取一个数据
class KS14_02_API CGetOneDataTask : public CSetOneDataTask
{
public:
    CGetOneDataTask() : CSetOneDataTask() {}
    virtual ~CGetOneDataTask() override {}
    virtual ETASKTYPE taskType() override { return ETASK_GETONEDATA; }
};
// 服务端返回一个数据给客户端
class KS14_02_API COneDataReturnedTask : public CGetOneDataTask
{
public:
	COneDataReturnedTask() : CGetOneDataTask() {}
	virtual ~COneDataReturnedTask() override {}
	virtual ETASKTYPE taskType() override { return ETASK_ONEDATARETURNED; }
};