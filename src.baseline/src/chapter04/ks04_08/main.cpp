/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。
\file: main.cpp
\brief QVariant的使用
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#include "qglobal.h"
#include <iostream>

void example01();
void example02();
void example03();
void example04();

using std::cout;
using std::endl;
using std::cin;

//
int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);


	// example01 
	if (0) {
		example01();
	}

	// example02 
	if (1) {
		example02();
	}

    // example03 
    if (0) {
        example03();
    }

    // example03 
    if (0) {
        example04();
    }

	char ch = '\0';
	cin >> ch;

	return 0;
}

/**
* @brief  常见Qt类与QVariant互相转换
* @return 无
*/
void example01(){
	
	
}
/**
* @brief  QVariant::value<>()的使用
* @return 无
*/
void example02(){
	
}

/**
* @brief  QVariantList的使用
* @return 无
*/
void example03() {


}

/**
* @brief  QVariant::nameToType(), QVariant::typeToName()
* @return 无
*/
void example04() {



}
