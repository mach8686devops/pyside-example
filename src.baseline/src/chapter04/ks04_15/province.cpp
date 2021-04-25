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

#include "province.h"
#include "city.h"

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
