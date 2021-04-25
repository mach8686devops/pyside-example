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
#include <QApplication>
#include <QFile>
#include <QMainWindow>
#include <QTextEdit>
#include <QTextStream>
#include "base/basedll/baseapi.h"

int main(int argc, char * argv[]) {
    QApplication app(argc, argv);
	
	QMainWindow mainWindow(NULL);
	QTextEdit textEdit(&mainWindow);
	QFile file;
	QString strFile = ns_train::getFileName("$TRAINDEVHOME/test/chapter09/ks09_01/input.txt");
	file.setFileName(strFile);
    QString str;
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream input(&file);
        input.setCodec("UTF-8"); // 读者可以试试用: GBK
        str = input.readAll();
    }

	textEdit.setText(str);

	mainWindow.setCentralWidget(&textEdit);
	mainWindow.show();

    return app.exec();
}
