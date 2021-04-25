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
#include <QTranslator>
#include <QLibraryInfo>
#include <QFile>
#include <QPixmap>
#include <QTextEdit>
#include <QTextStream>
#include <QThread>
#include "mainwindow.h"
#include "splashscreen.h"

int main(int argc, char * argv[]) {
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
	strPath += "/system/lang";					// $TRAINDEVHOME/system/lang/ks03_01.qm
	QScopedPointer<QTranslator> gpTranslator(new QTranslator(QCoreApplication::instance()));
	if (gpTranslator->load("ks08_03.qm", strPath)) {
		QCoreApplication::installTranslator(gpTranslator.take());
	}

	QPixmap pixmap(":/images/logo.png");
	CSplashScreen splashScreen(pixmap);
	splashScreen.show(); // 显示启动窗
	QThread::msleep(1);  // 保证在Linux上可以正常显示出来，
						 // 否则只有进度100%时才能显示。
	app.processEvents(); // 保证显示启动画面的同时仍可以正常响应鼠标、键盘等操作 
   	
	CMainWindow mainWindow(NULL, &splashScreen);
	splashScreen.finish(&mainWindow); // 等待主窗口初始化完毕，然后隐藏splashScreen
	mainWindow.showMaximized();

    return app.exec();
}
