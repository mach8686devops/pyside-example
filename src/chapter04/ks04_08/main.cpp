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
#include <QColor>
#include <QFont>
#include <QPointF>
#include <QVariant>

#include <iostream>

void example01();
void example02();
void example03();
void example04();

using std::cout;
using std::endl;
using std::cin;

//
int main(int argc, char * argv[]) {
	Q_UNUSED(argc);
	Q_UNUSED(argv);


	// example01 
	if (0) {
		example01();
	}

	// example02 
	if (0) {
		example02();
	}

    // example03 
    if (0) {
        example03();
    }

    // example04
    if (1) {
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
	// 整数
    QVariant var1(1);
    cout << "this is an integer:" << var1.toInt() << endl;

    // 无符号整数
    uint uVal = 599;
    QVariant var2(uVal);
    cout << "this is an unsigned integer:" << var2.toUInt() << endl;

    // 双精度浮点数
    qreal dVal = 100.23456;
    QVariant var3(dVal);
    cout << "this is a double:" << var3.toDouble() << endl;
    cout << "this is a double:" << var3.toString().toLocal8Bit().data() << endl;

    // 字符串
    QString str("I'm a string!");
    QVariant var4(str);
    cout << "this is a string:" << var4.toString().toLocal8Bit().data() << endl;
    //qDebug() << var4;
	
    // QPointF
    QPointF pt(100.34, 200.1);
    QVariant var5(pt);
    cout << "this is a QPointF:" << var5.toPointF().x() << ", " << var5.toPointF().y() << endl;
}
/**
* @brief  QVariant::value<>()的使用
* @return 无
*/
void example02(){

    // QVariant 与 QColor 互相转换
    QColor clr1(Qt::darkMagenta);
    QVariant var1(clr1);
    cout << "clr1:" << clr1.redF() << ", " << clr1.greenF() << ", " << clr1.blueF() << endl;

    // 将var1还原为QColor
    QColor clr2 = var1.value<QColor>();
    cout << "clr2:" << clr2.redF() << ", " << clr2.greenF() << ", " << clr2.blueF() << endl;


    // QVariant 与 QFont 互相转换
    QFont ft1(QString::fromLocal8Bit("宋体"));
    ft1.setPointSizeF(12.6);
    QVariant var2(ft1);
    QFont ft2 = var2.value<QFont>();
    cout << "font, family:"
        << ft2.family().toLocal8Bit().data()
        << ", point size = "
        << ft2.pointSizeF()
        << endl;
}

/**
* @brief  QVariantList的使用
* @return 无
*/
void example03() {
    // 整数
    QVariant var1(1);

    // 无符号整数
    uint uVal = 599;
    QVariant var2(uVal);

    // 双精度浮点数
    qreal dVal = 100.23456;
    QVariant var3(dVal);

    // 字符串
    QString str("I'm a string!");
    QVariant var4(str);

    // QPointF
    QPointF pt(100.34, 200.1);
    QVariant var5(pt);

    QVariantList lst;
    lst << var1 << var2 << var3 << var4 << var5;

    QVariant var;
    QVariantList::iterator iteLst = lst.begin();
    for (; iteLst != lst.end(); iteLst++) {
        var = *iteLst;
        cout << "type is " << var.typeName() << ", value is ";
        switch (var.type()) {
        case QVariant::Int:
            cout << var.toInt() << endl;
            break;
        case QVariant::UInt:
             cout << var.toUInt() << endl;
            break;
        case QVariant::Double:
            cout << var.toDouble() << endl;
            break;
        case QVariant::String:
            cout << var.toString().toLocal8Bit().data() << endl;
            break;
        case QVariant::PointF:
            cout << "x = " << var.toPointF().x() << ", y = " << var.toPointF().y() << endl;
            break;
       default:
            cout << "default"<< endl;
            break;
        }
    }
}

/**
* @brief  QVariant::nameToType(), QVariant::typeToName()
* @return 无
*/
void example04() {

    cout << QVariant::typeToName(QVariant::Int) << endl;   // "int"
    cout << QVariant::typeToName(QVariant::PointF) << endl; // "QPointF"

    qreal dVal = 100.23456;
    QVariant var3(dVal);
    cout << QVariant::nameToType(var3.typeName()) << endl; // 6

}
