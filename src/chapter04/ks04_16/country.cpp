﻿/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: country.cpp
\brief 国家类实现文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/10
*/
#include <QDir>

#include "base/basedll/baseapi.h"
#include "country.h"
#include "province.h"

CCountry::CCountry() {
	;
}

CCountry::~CCountry() {
	clear();
}

void CCountry::clear(void) {
	QList<CProvince*>::iterator iteLst = m_lstProvinces.begin();
	while (iteLst != m_lstProvinces.end()) {
		if (NULL != *iteLst) {
			delete *iteLst;
		}
		iteLst++;
	}
	m_lstProvinces.clear();
}

int CCountry::addProvince(CProvince* pProvince) {
	if ((NULL == pProvince) || (m_lstProvinces.contains(pProvince))) {
		return m_lstProvinces.size();
	}

	m_lstProvinces.push_back(pProvince);
	return m_lstProvinces.size();
}

ESerializeCode CCountry::serializeBinary(const QString& strFileName, QString* pError) const {
	if (0 == strFileName.length()) {
		if (NULL != pError) {
			pError->append(QString::fromLocal8Bit("\n文件名为空"));
		}
		return ESERIALIZECODE_FILENOTFOND;
	}
	QFile file(strFileName);
	QString strDirectory = ns_train::getDirectory(strFileName);
	
	QDir dir;
	dir.mkpath(strDirectory);

	if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
		return ESERIALIZECODE_FILENOTFOND;
	}

	QDataStream ds(&file);
	ds.setByteOrder(QDataStream::LittleEndian);
	ESerializeCode ret = serializeBinary(ds, pError);
	file.close();

	return ret;
}

ESerializeCode  CCountry::serializeBinary(QDataStream& ds, QString* pError) const {
	ds.setByteOrder(QDataStream::LittleEndian); 
	ds << m_strName;
	ds << m_strContinent;
	quint16 nCount = m_lstProvinces.size(); // 需要明确指定数据类型，否则跨平台时可能出问题。比如int在各个平台上可能长度不一样。
	ds << nCount; 
	QList<CProvince*>::ConstIterator iteLst = m_lstProvinces.constBegin(); // 因为本函数为const，所以需要调用const类型的接口
	ESerializeCode ret = ESERIALIZECODE_OK;
	while (iteLst != m_lstProvinces.end()) {
		ESerializeCode retcode = (*iteLst)->serializeBinary(ds, pError);
		if (ESERIALIZECODE_OK != retcode) {
			ret = retcode;
		}
		iteLst++;
	}
	return ret;
}

ESerializeCode CCountry::deSerializeBinary(const QString& strFile, QString* pError) {
	Q_UNUSED(pError);
	clear();

	if (strFile.isEmpty())	{
		return ESERIALIZECODE_FILENOTFOND;
	}
	QString strFileName = ns_train::getPath(strFile);

	QFile file(strFileName);
	if (!file.open(QFile::ReadOnly))	{
		return ESERIALIZECODE_FILENOTFOND;
	}

	QDataStream ds(&file);
	ESerializeCode ret = deSerializeBinary(ds, pError);
	file.close();

	return ret;
}

ESerializeCode CCountry::deSerializeBinary(QDataStream& ds, QString* pError) {
	clear();

	ds.setByteOrder(QDataStream::LittleEndian);
	ESerializeCode retcode = ESERIALIZECODE_OK;
	ds >> m_strName;
	ds >> m_strContinent;
	quint16 nCount = 0; // 需要明确指定数据类型，否则跨平台时可能出问题。比如int在各个平台上可能长度不一样。
	ds >> nCount;
	quint16 idx = 0;
	CProvince* pProvince = NULL;

	for (idx = 0; idx < nCount; idx++) {
		pProvince = new CProvince();
		pProvince->deSerializeBinary(ds, pError);
		addProvince(pProvince);
		pProvince->setCountry(this);
	}

	return retcode;
}
