/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: main.cpp
\brief main()函数的实现文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/


#include <iostream>
#include "base/basedll/baseapi.h"

#include "qglobal.h"
#include "country.h"
#include "province.h"
#include "city.h"


CCountry* createCountry(void);

int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);


	return 0;
}


/**
* @brief构建CCountry对象.
* @return CCountry对象指针
*/
CCountry* createCountry(void) {
	CProvince* pProvince = NULL;
	CCity* pCity = NULL;
	CCountry* pCountry = new CCountry(QString::fromLocal8Bit("中国"));
	if (NULL == pCountry) {
		return NULL;
	}
	// add province
	{
		pProvince = new CProvince();
		pCountry->addProvince(pProvince);
		pProvince->setCountry(pCountry);
		pProvince->setName(QString::fromLocal8Bit("山东"));
		// add city
		pCity = new CCity();
		pCity->setName(QString::fromLocal8Bit("济南"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);

		// add city
		pCity = new CCity();
		pCity->setName(QString::fromLocal8Bit("青岛"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);
	}
	// add province
	{
		pProvince = new CProvince();
		pCountry->addProvince(pProvince);
		pProvince->setCountry(pCountry);
		pProvince->setName(QString::fromLocal8Bit("河北"));
		// add city
		pCity = new CCity();
		pCity->setName(QString::fromLocal8Bit("北戴河"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);

		// add city
		pCity = new CCity();
		pCity->setName(QString::fromLocal8Bit("张家口"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);

		// add city
		pCity = new CCity();
		pCity->setName(QString::fromLocal8Bit("保定"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);
	}

	// 返回构建的CCountry对象
	return pCountry;
	
}
