/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: myclass.h
\brief exe+dll编程示例，引出类CPrint的定义头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9 
* please import ks04_01_dll.dll
*/

#pragma once 

#include "ks04_01_export.h"
/// 打印类CPrint定义
class KS04_01_Export CPrint {
public:
	CPrint(){}
	~CPrint(){}
public:
	/**
	* @brief 将指定信息打印到屏幕
	* @param[in] szInfo  待打印的信息
	* @return void
	*/
	void printOnScreen(const char*);
};

KS04_01_Export int func1();
KS04_01_Export int func2(int, float);
