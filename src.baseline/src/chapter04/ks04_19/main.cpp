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

#include <QCoreApplication>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QDir>
#include <QFile>
#include "qglobal.h"
#include <QString>
#include <iostream>


using std::cin;

void example01();
void example02();


int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);

	QCoreApplication app(argc, argv);
   

	if (1) {
		example01();
	}

	if (1) {
		example02();
	}
	
	char ch = '\0';
	cin >> ch;

	return 0;
}

/**
* @brief 保存xml格式文件示例代码
*        xml文件内容
*       --------------------------------------------------------------------
*       <?xml version="1.0" encoding="GB2312" standalone="yes"?>
*       <!--软件特攻队-->
*       <doc>
*           <courses count="4" institution="软件特攻队" teacher="女儿叫老白">
*               <lesson url="https://study.163.com/instructor/1143174933.htm" id="1" fee="免费">C++老鸟日记</lesson>
*               <lesson url="https://study.163.com/instructor/1143174933.htm" id="2" fee="免费">C++跨平台开发中的编译错误</lesson>
*               <lesson url="https://study.163.com/instructor/1143174933.htm" id="3">Qt 5/PyQt 5实战指南（C++版）</lesson>
*               <lesson url="sorry, not ready" id="4">C++跨平台服务模块开发</lesson>
*           </courses>
*       </doc>
*
*/
void example01() {

}

/**
* @brief 读取xml格式文件示例代码
*/
void example02() {

}
