/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: fileattribute.h
\brief 文件属性的访问类定义
\author 女儿叫老白@软件特攻队
\Date : 2018/1/10
* please import basedll.dll
*/

#pragma once


#include <QString>
#include "qglobal.h"

#include "base_export.h"
#include "base/basedll/serialize.h"


class QDomElement;

namespace ns_train {
	
static const quint16 c_MainVersion = 1;		/// 当前的主版本号
static const quint16 c_SubVersion = 12;		/// 当前的次版本号

const quint16 c_MD5_Length = 16;			/// md5码的长度，单位：字节。
/// 文件的属性
struct BASE_API SFileAttr {
	quint16	mainVer;						/// 主版本号
	quint16	subVer;							/// 次版本号
	quint8	md5[c_MD5_Length];				/// 本文件的md5码, 二进制格式使用，文本格式不用该属性。

	SFileAttr(){ mainVer = 1; subVer = 0; memset(md5, 0, c_MD5_Length); }
};
/// 序列化文件的自定义属性(二进制)
BASE_API QDataStream& operator<<(QDataStream& stream, const SFileAttr& attrs);
/// 反序列化文件的自定义属性(二进制)
BASE_API QDataStream& operator>>(QDataStream& stream, SFileAttr& attrs);
/// 序列化文件的基本数据(XML)
BASE_API QDomElement& operator<<(QDomElement& ele, const SFileAttr& attrs);
/// 反序列化文件的基本数据(XML)
BASE_API QDomElement& operator>>(QDomElement& ele, SFileAttr& attrs);

//！读取文件的属性-二进制方式
/**
* @param[in] fileName	文件全路径名
* @param[out] attrs		属性
* @retval ESerializeCode
*/
BASE_API ESerializeCode readInfoFromBinary(const QString& fileName, SFileAttr& attrs);

//！读取文件的属性-xml方式
/**
* @param[in] fileName	文件全路径名
* @param[out] attrs		属性
* @retval ESerializeCode
*/
BASE_API ESerializeCode readInfoFromXML(const QString& fileName, SFileAttr& attrs);
/// 获取当前文件的主版本号（使用本程序保存文件时的版本号）
quint16 getMainVersion() {
    return c_MainVersion;
}
/// 获取当前文件的次版本号（使用本程序保存文件时的版本号）
quint16 getSubVersion() {
        return c_SubVersion;
}

} // namespace iesgp

