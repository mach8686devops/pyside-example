/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dll.cpp
\brief	
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9 
*/
#include "config.h"
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QDir>
#include "base/basedll/baseapi.h"


///////////////////////////////////////////////////////////////////
CConfig CConfig::m_config;
CConfig::CConfig(): m_bAuthorized(false) {
	m_styleSheetLeftDark = QLatin1String("background-color: rgb(17, 149, 189);\n"
		"border-top-left-radius:5px;\n"
		"border-bottom-left-radius:5px;\n"
		"border-width:1px; border-style: solid");
	m_styleSheetRightDark = QLatin1String("background-color: rgb(17, 149, 189);\n"
		"border-top-right-radius:5px;\n"
		"border-bottom-right-radius:5px;\n"
		"border-width:1px; border-style: solid");
	m_styleSheetBaseDark = QLatin1String("background-color: rgb(17, 149, 189);border-width:1px; border-style: solid");
	m_styleSheetLeft = QLatin1String("background-color: rgb(17, 149, 189);\n"
		"border-top-left-radius:5px;\n"
		"border-bottom-left-radius:5px;border-width:1px;border-style:dashed");
	m_styleSheetRight = QLatin1String("background-color: rgb(17, 149, 189);\n"
		"border-top-right-radius:5px;\n"
		"border-bottom-right-radius:5px;border-width:1px; border-style:dashed");
	m_styleSheetBase = QLatin1String("background-color:rgb(17, 149, 189);border-width:1px; border-style:dashed");
	m_styleSheetA = QLatin1String("background-color: rgb(255, 255, 255);\nborder-radius:5px;");
	m_styleSheetB = QLatin1String("background-color: rgb(255, 255, 255);");

	// 创建并打开数据库
	m_database = QSqlDatabase::addDatabase("QSQLITE");
	QString strDir = ns_train::getPath("$TRAINDEVHOME/test/chapter23/ks23_03/");
	QDir dir(strDir);
	if (!dir.exists())
		dir.mkpath(strDir);
	QString strFile = strDir + "ks23_03_database.dbfile";
	m_database.setDatabaseName(strFile);
	m_database.setUserName("admin");      // 数据库用户名   
	m_database.setPassword("admin1235");  // 数据库密码  

}

CConfig& CConfig::instance() {
    return m_config;
}

bool CConfig::connectToDatabase() {
	return m_database.open();
}

