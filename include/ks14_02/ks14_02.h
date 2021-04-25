﻿/*!
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

// 动态库导出宏定义
#ifdef WIN32		// windows platform
#	if defined __KS14_02_COMMUNICATE_SOURCE__
#		define KS14_02_API __declspec(dllexport)
#	else
#		define KS14_02_API __declspec(dllimport)
#	endif

#else				// other platform
#  define KS14_02_API
#endif // WIN32