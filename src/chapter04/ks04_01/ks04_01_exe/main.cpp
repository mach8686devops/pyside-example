/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: main.cpp
\brief main()函数的实现文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/8
*/
#include <iostream>

#include "qglobal.h"
#include "ks04_01/myclass.h"

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char * argv[]) {
	Q_UNUSED(argc);
	Q_UNUSED(argv);

	CPrint pr;
	pr.printOnScreen("it is a test!");

	func1();
	func2(2, 3.f);

	char ch = '\0';
	cin >> ch;
	return 0;
}
