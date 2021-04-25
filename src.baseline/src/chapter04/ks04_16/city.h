﻿/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: city.h
\brief 城市类定义文件。
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/10
*/

#pragma once
#include<QString>

#include "serialize.h"

class CProvince;

// 城市类
//-----------------------------------------
class CCity
{
public:
	CCity();
	~CCity();

    /**
    * @brief 设置城市名称.
    * @param[in] str 城市名称
    * @return void
    */
	void  setName(const QString& str) {m_strName = str;}

    /**
    * @brief 获取城市名称.
    * @return 城市名称
    */
	QString  getName(void)const {return m_strName;}
 
    /**
    * @brief 设置城市所在省(州)
    * @param[in] pProvince 城市所在省(州)
    * @return void
    */
	void  setProvince(CProvince* pProvince) { m_pProvince = pProvince;}

    /**
    * @brief 获取城市所在省(州)
    * @return 城市所在省(州)
    */
	CProvince*  getProvince(void) const {return m_pProvince;}
	/**
	* @brief 用来把类对象进行二进制方式序列化的函数。本接口内部已经调用QDataStream::setByteOrder(QDataStream::LittleEndian)。
	* @param[in] ds 文件流对象。
	* @param[in|out] pError 错误信息。
	* @return ESerializeCode枚举值。
	*/
	ESerializeCode serializeBinary(QDataStream& ds, QString* pError) const;

private:	
    QString	m_strName;
	CProvince*	m_pProvince;
};


