/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: serialize.h
\brief 序列化错误码定义文件。
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/10
*/
#pragma once

/**
* @brief 序列化错误码的枚举
*
* ESerializeCode 枚举。
* 用来说明序列化时出现错误的原因
*
*/
enum ESerializeCode {
	ESERIALIZECODE_OK = 0,				/// 正常
	ESERIALIZECODE_FILENOTFOND,			/// 文件不存在
	ESERIALIZECODE_ELEMENT_NOTFOUND,	/// doc元素不存在
	ESERIALIZECODE_SETCONTENT_ERROR,	/// QDomDocument::setContent()调用失败
	ESERIALIZECODE_GRAPHVERSION_NOTRECOGNIZE,	/// 图形版本不识别
	ESERIALIZECODE_OTHERERROR,					/// 其他错误

};
