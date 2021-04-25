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

//#include "qglobal.h"
#include <QString>
#include <QRectF>
#include <QObject>
#include <QDebug>
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

#include <iostream>


void example01();
void example02();
void example03();

using std::cin;
int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);
	QApplication app(argc, argv);

	// 国际化
	// 安装qt自带的中文翻译
	const QString localSysName = QLocale::system().name();
	QScopedPointer<QTranslator> qtTranslator(new QTranslator(QCoreApplication::instance()));
	if (qtTranslator->load(QStringLiteral("qt_") + localSysName,
		QLibraryInfo::location(QLibraryInfo::TranslationsPath))) {
		QCoreApplication::installTranslator(qtTranslator.take());
	}

	// 安装我们项目的翻译文件
	QString strPath = qgetenv("TRAINDEVHOME");	// 获取环境变量所指向的路径
	strPath += "/system/lang";					// $TRAINDEVHOME/system/lang/ksxx_xx.qm
	QScopedPointer<QTranslator> gpTranslator(new QTranslator(QCoreApplication::instance()));
	if (gpTranslator->load("ks04_04.qm", strPath)) {
		QCoreApplication::installTranslator(gpTranslator.take());
	}

	// example01 
	if (0) {
		example01();
	}

	// example02 
	if (1) {
		example02();
	}
	
	// example03 
	if (1) {
		example03();
	}

	cout << "please input any key to exit......";
	char ch = '\0';
	cin >> ch; // 键入任意字符退出

	return 0;
}

/**
* @brief  qDebug()<< 方式输出信息
*		  可以直接用<<操作符将需要输出的信息输出到qDebug()。
* @return 无
*/
void example01(){
	
	

}

/**
* @brief  使用qDebug("%")格式化输出信息
* @return 无
*/
void example02(){
	
	
}


/**
* @brief  将自定义类输出到qDebug
* @param[in] mc 自定义类
* @return 
*/
void example03(){
	
}
