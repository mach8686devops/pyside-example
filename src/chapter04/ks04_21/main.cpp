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

#include "base/basedll/baseapi.h"
#include <string>
#include <QTextCodec>
#include <QTextStream>
#include <QDir>
#include <QFile>
#include <QDebug>
/**
* @brief 解析身份证信息文件并将解析后的结果输出到终端。
*        身份证信息文件编码为GB13000，可以认为是UTF-16编码，即双字节编码。
*        因此身份证信息格式中的2个字节用来表示1个字符。在访问该QString对象时，
*        应该将字节数/2。
* @return 当前子目录名
*/
void parse_id() {
    QFile file;
    QString strFileName = ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_21/id.txt");
    file.setFileName(strFileName);
    if (!file.open(QFile::ReadOnly)){
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-16");
    QString stra = in.readAll();
   // qDebug() << "characters:"<< stra.length();
   // qDebug() << "file contents:" << stra.toUtf8().data();

    // 字符串数组的长度应该比规定中多一个字节，最后一个字节用来存放C++字符串中的结束符'\0'。
    char sz_Name[30+1];

    // “姓名”本来是30字节，但实际表示的字符数为：15=30/2。下面这行代码中的最后一个参数仍然要用30，因为已经用toUtf8()将数据转换成单字节字符串了。
    // 姓名，字符序号:0~14
    strncpy(sz_Name, stra.left(15).toUtf8().data(), 30);
    sz_Name[30] = '\0';// 务必增加字符串结束符
    qDebug() << "name:" <<sz_Name;

    // 性别，字符序号:15
    quint16 u16Sex = 0;
    u16Sex = stra.mid(30/2, 2/2).toUShort(); // 第15个字符是性别
    qDebug() << "sex:" << u16Sex;

    // 民族，字符序号:16~17
    quint16 u16Nationality=0;
    u16Nationality = stra.mid(32/2, 4/2).toUShort(); // 第16个字符开始的2个字符是民族
    qDebug() << "Nationality:" << u16Nationality;

    // 出生日期，字符序号:18~25
    quint16 u16Year = 0;
    u16Year = stra.mid(36/2, 8/2).toUShort(); // 第18个字符开始的4个字符是生日中的年
    qDebug() << "Birthday Year:" << u16Year;

    quint16 u16Month = 0;
    u16Month = stra.mid(44/2, 4/2).toUShort(); // 第22个字符开始的2个字符是生日中的月
    qDebug() << "Birthday Month:" << u16Month;

    quint16 u16Day = 0;
    u16Day = stra.mid(48/2, 4/2).toUShort();  // 第24个字符开始的4个字符是生日中的年
    qDebug() << "Birthday Day:" << u16Day;

    // 住址，字符序号:26~60
    char sz_Address[70+1];
    strncpy(sz_Address, stra.mid(52/2, 70/2).toUtf8().data(), 70);
    sz_Address[70] = '\0';// 务必增加字符串结束符
    qDebug() << "Address:" <<sz_Address;

    // 公民身份证号码，字符序号:61~78
    char sz_Id[36+1];
    strncpy(sz_Id, stra.mid(122/2, 36/2).toUtf8().data(), 36);
    sz_Id[36] = '\0';// 务必增加字符串结束符
    qDebug() << "Id:" <<sz_Id;

    // 签发机关，字符序号:79~93
    char sz_Authority[30+1];
    strncpy(sz_Authority, stra.mid(158/2, 30/2).toUtf8().data(), 30);
    sz_Authority[30] = '\0';// 务必增加字符串结束符
    qDebug() << "Authority:" <<sz_Authority;

    // 有效期起始日期，字符序号:94~101
    u16Year = stra.mid(188/2, 8/2).toUShort(); // 第94个字符开始的4个字符是“有效期起始日期”中的年
    u16Month = stra.mid(196/2, 4/2).toUShort(); // 第98个字符开始的2个字符是“有效期起始日期”中的月
    u16Day = stra.mid(200/2, 4/2).toUShort(); // 第100个字符开始的2个字符是“有效期起始日期”中的日
    qDebug() << "Valid from:" << u16Year << "-" << u16Month << "-" << u16Day;

    // 有效期终止日期，字符序号:102~109
    u16Year = stra.mid(204/2, 8/2).toUShort(); // 第102个字符开始的4个字符是“有效期终止日期”中的年
    u16Month = stra.mid(212/2, 4/2).toUShort(); // 第106个字符开始的2个字符是“有效期终止日期”中的月
    u16Day = stra.mid(216/2, 4/2).toUShort(); // 第108个字符开始的2个字符是“有效期终止日期”中的日
    qDebug() << "Expire from:" << u16Year << "-" << u16Month << "-" << u16Day;
}
void write_id() {
    QFile file;
    QString strFileName = ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_21/id.txt");
    QString strDirectory = ns_train::getDirectory(strFileName);
    QDir dir;
    dir.mkpath(strDirectory);
    file.setFileName(strFileName);
    if (!file.open(QFile::WriteOnly)){
        return;
    }
    QTextStream out(&file);
    out.setCodec("UTF-16");
    QString stra;
    QString str;

    //char sz_str[128];
    // 姓名:15字符
    str = QString::fromLocal8Bit("我是：女儿叫老白");
    str.resize(15);
    stra = str;

    // 性别:1字符
    str = QString("0");
    str.resize(1);
    stra += str;

    // 民族:2字符
    str = QString("02");
    str.resize(2);
    stra += str;

    // 出生日期:8字符
    str.sprintf("20190101");
    stra += str;
    // 住址:35字符
    str = QString::fromLocal8Bit("A市B小区C栋D单元101");
    str.resize(35);
    stra += str;

    // 公民身份证号码:18字符
    str.sprintf("379902201901013731");
    str.resize(18);
    stra += str;

    // 签发机关:15字符
    str = QString::fromLocal8Bit("A市公安局H分局");
    str.resize(15);
    stra += str;

    // 有效期起止日期:8字符
    str.sprintf("20190101");
    stra += str;

    // 有效期截止止日期:8字符
    str.sprintf("20290101");
    stra += str;
    out << stra;  
    file.close();
}
int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);

    write_id();
    parse_id();

	return 0;
}
