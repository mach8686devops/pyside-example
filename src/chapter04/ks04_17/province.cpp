﻿/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: country.cpp
\brief 省类实现文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/10
*/

#include "city.h"
#include "province.h"

// tag name
static const char* c_tag_city = "city";

// attribute name
static const char* c_attribute_name = "name";

CProvince::CProvince() {
	;
}

CProvince::~CProvince() {
	QList<CCity*>::iterator iteLst = m_lstCities.begin();
	while (iteLst != m_lstCities.end()) {
		if (NULL != *iteLst) {
			delete *iteLst;
		}
		iteLst++;
	}

	m_lstCities.clear();
}

int CProvince::addCity(CCity* pCity) {
	if ((NULL == pCity) || (m_lstCities.contains(pCity))) {
		return m_lstCities.size();
	}

	m_lstCities.push_back(pCity);
	return m_lstCities.size();
}

ESerializeCode  CProvince::serializeBinary(QDataStream& ds, QString* pError) const {
	ds << m_strName;
	quint16 nCount = m_lstCities.size(); // 需要明确指定数据类型，否则跨平台时可能出问题。比如int在各个平台上可能长度不一样。
	ds << nCount;
	QList<CCity*>::ConstIterator iteLst = m_lstCities.constBegin(); // 因为本函数为const，所以需要调用const类型的接口
	while (iteLst != m_lstCities.end()) {
		(*iteLst)->serializeBinary(ds, pError);
		iteLst++;
	}

	return ESERIALIZECODE_OK;
}


ESerializeCode CProvince::deSerializeBinary(QDataStream& ds, QString* pError) {
	ds.setByteOrder(QDataStream::LittleEndian);
	ESerializeCode retcode = ESERIALIZECODE_OK;
	ds >> m_strName;
	quint16 nCount = 0; // 需要明确指定数据类型，否则跨平台时可能出问题。比如int在各个平台上可能长度不一样。
	ds >> nCount;
	quint16 idx = 0;
	CCity* pCity = NULL;

	for (idx = 0; idx < nCount; idx++) {
		pCity = new CCity();
		pCity->deSerializeBinary(ds, pError);
		addCity(pCity);
	}

	return retcode;
}


ESerializeCode CProvince::serializeXML(QDomDocument& doc, QDomElement& eleProvince, QString* pError) const
{
    eleProvince.setAttribute(c_attribute_name, m_strName);

    ESerializeCode ret = ESERIALIZECODE_OK;

    QList<CCity*>::ConstIterator iteList = m_lstCities.constBegin();
    while (iteList != m_lstCities.constEnd())   {
        QDomElement eleCity = doc.createElement(c_tag_city);
        ESerializeCode retcode = (*iteList)->serializeXML(doc, eleCity, pError);
        if (ESERIALIZECODE_OK != retcode) {
            ret = retcode;
        }
        eleProvince.appendChild(eleCity);
        iteList++;
    }

    return ret;
}

ESerializeCode CProvince::deSerializeXML(const QDomElement& eleProvince, QString* pError)
{
    m_strName = eleProvince.attribute(c_attribute_name);
    QDomElement eleCity = eleProvince.firstChildElement();
    CCity* pCity = NULL;
    ESerializeCode ret = ESERIALIZECODE_OK;
    while (!eleCity.isNull()) {
        pCity = new CCity;
        addCity(pCity);

        ret = pCity->deSerializeXML(eleCity, pError);
        if (ESERIALIZECODE_OK != ret) {
            return ret;
        }
        eleCity = eleCity.nextSiblingElement();
    }
    return ret;
}
