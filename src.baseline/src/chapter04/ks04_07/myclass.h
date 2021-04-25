/*! * Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: myclass.h
\brief exe+dll编程示例，引出类的定义头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9 
*/

#pragma once
#include <QString>

class CMyClass
{
public:
	// 构造函数
	CMyClass(): m_id(0), m_pStrName(NULL){}
	// 构造函数
	CMyClass(int id, const QString& name): m_id(id), m_pStrName(new QString(name)){}

	// 析构函数
	~CMyClass();


	/**
	* @brief  设置id
	* @param[in] id id
	*/
	void setId(int id) { m_id = id; }
	/**
	* @brief  获取id
	* @return id
	*/
	int getId() const { return m_id; }

	/**
	* @brief  设置名字
	* @param[in] name 名字
	*/
	void setName(const QString& str);
	/**
	* @brief  获取名字
	* @return 名字
	*/
	QString getName() const;
private:
	int m_id;
	QString* m_pStrName;
};

