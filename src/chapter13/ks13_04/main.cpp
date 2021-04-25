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
#include <qtconcurrentmap.h>
#include <iostream>
#include "baseapi.h"

using std::cout;
using std::endl;
typedef QMap<QString, QByteArray> MD5Map;

/**
* @brief  reduce函数
* @param[in|out] result reduce函数的返回数据存放到result。
* @param[in] w 执行完map函数得到的结果w作为输入传入reduce函数。
* @return void
*/
void reduce(MD5Map &result, const MD5Map &w) {
	QMapIterator<QString, QByteArray> i(w);
	while (i.hasNext()) {
		i.next();
		result[i.key()] += i.value();
	}
}
/**
* @brief  map函数
* @param[in] strFileName 待计算md5码的文件名。
* @return MD5Map 计算出的文件名到md5码的映射，该值将被用来调用reduce接口(作为接口的参数2)
*/
MD5Map getMd5OfFile(const QString& strFileName) {
	qDebug() << "get md5 in thread" << QThread::currentThread();
	MD5Map md5map;
	md5map[strFileName] = ns_train::getMd5(strFileName);
	return md5map;
};

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
	int mapReduceTime = 0;
	MD5Map md5_b;
	{
		QTime time;
		time.start();
		md5_b = QtConcurrent::mappedReduced(files, getMd5OfFile, reduce);
		mapReduceTime = time.elapsed();
		qDebug() << "file count:" << files.count();
		qDebug() << "single thread" << singleThreadTime;
		qDebug() << "MapReduce" << mapReduceTime;
	}

	qDebug() << "Map speedup x" << ((double)singleThreadTime - (double)mapReduceTime) / (double)mapReduceTime + 1;

    // 将结果b写入文件
    {
        QString strFileName;
        strFileName = ns_train::getPath("$TRAINDEVHOME/test/chapter13/ks13_04/md5_b.txt");
        QString strDir = ns_train::getDirectory(strFileName);
        QDir dir;
        dir.mkpath(strDir);

        QFile file(strFileName);
        // 打开方式：只读、文本方式
        if (!file.open(QFile::Truncate | QFile::WriteOnly | QFile::Text)) {
            qDebug("open failed! file name is:%s", strFileName.toLocal8Bit().data());
        }
        else {
            QMapIterator<QString, QByteArray> iteMd5(md5_b);
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
