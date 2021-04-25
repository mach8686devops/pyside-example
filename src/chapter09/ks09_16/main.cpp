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
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QTranslator>
#include <QLibraryInfo>
#include <QFile>
#include <QDebug>
//#include <QTextStream>
//#include "mainwindow.h"

int main(int argc, char * argv[]) {
    QApplication app(argc, argv);
    // 解析命令行参数
    // -f="c:/dir/fielname.dat"
    QCommandLineOption op1("f");
    op1.setValueName("path"); // 期望值是路径，设置了ValueName后。解析器会觉得此命令带值
    QCommandLineParser parser;
    parser.addOption(op1);
    parser.process(app);
    if (parser.isSet("f")) {
        qDebug() << parser.value(op1);// "c:/dir/fielname.dat"
    }
        
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
    if (gpTranslator->load("ks09_16.qm", strPath)) {
		QCoreApplication::installTranslator(gpTranslator.take());
	}

#ifdef WIN32
//	WSADATA  wsaData;
//	if (WSAStartup (0x202, &wsaData) != 0)
//		return false;
#endif

    return app.exec();
}
