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
#include <QTranslator>	// 国际化
#include "qglobal.h"
#include <QLibraryInfo> // 国际化

#include <QDir> 
#include <QFile> 
#include <iostream>
#include "baseapi.h"

using std::cout;
using std::endl;
typedef QMap<QString, QByteArray> MD5Map;

int main(int argc, char * argv[]) {
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
	strPath += "/system/lang";					// $TRAINDEVHOME/system/lang/xxxxx.qm
	QScopedPointer<QTranslator> gpTranslator(new QTranslator(QCoreApplication::instance()));
	if (gpTranslator->load("ks13_03.qm", strPath)) {
		QCoreApplication::installTranslator(gpTranslator.take());
	}

    QStringList strFilters;
    strFilters << "*.h" << "*.cpp"; // 需要注意避免把本demo产生的md5_a.txt、md5_b.txt统计在内。

    // 得到待计算MD5码的文件列表.
    QString strScanPath = ns_train::getPath("$TRAINDEVHOME");
    qDebug() << strScanPath;
    QStringList files = ns_train::getFileList(strScanPath, strFilters, true);
    QStringList::iterator ite = files.begin();
   
    int singleThreadTime = 0; // 单线程计算md5码所需的时间。
    QTime time;
    time.start();
    MD5Map md5_a;
    { // 串行操作
        QString strFileName;
        for (; ite != files.end(); ite++) {
            md5_a[*ite] = ns_train::getMd5(*ite);
        }
        singleThreadTime = time.elapsed(); // ms
        qDebug() << "single thread" << singleThreadTime;
    }
    // 将结果a写入文件
    {
        QString strFileName;
        strFileName = ns_train::getPath("$TRAINDEVHOME/test/chapter13/ks13_04/md5_a.txt");
        QString strDir = ns_train::getDirectory(strFileName);
        QDir dir;
        dir.mkpath(strDir);
    
        QFile file(strFileName);
        // 打开方式：只读、文本方式
        if (!file.open(QFile::Truncate | QFile::WriteOnly | QFile::Text)) {
            qDebug("open failed! file name is:%s", strFileName.toLocal8Bit().data());
        }
        else {
            QMapIterator<QString, QByteArray> iteMd5(md5_a);
            while (iteMd5.hasNext()) {
                iteMd5.next();
                file.write(iteMd5.key().toLocal8Bit());
                file.write(iteMd5.value());
            }
        }
        file.close();
    }   

 	return 0;
}
