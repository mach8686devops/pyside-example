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

#include "base/basedll/baseapi.h"

using std::cin;
void example01();
void example02();

void parseDoc(QXmlStreamReader& reader);
void parseCourses(QXmlStreamReader& reader);
void parseLesson(QXmlStreamReader& reader);

int main(int argc, char * argv[]) {
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
    QString strPath = 
        ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_19");
    if (!strPath.endsWith("/")) {
        strPath += "/";
    }
    QDir dir(strPath);
    dir.mkpath(strPath);
    QString strFileName = strPath + "test04_19.xml";
    QFile file(strFileName);
    if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate)) {// QFile::Truncate：为了清空原来的文件内容
        return;
    }
    QXmlStreamWriter writer(&file);    
    writer.setCodec("UTF-8");// 设置XML编码
    writer.setAutoFormatting(true); // 自动格式化
    writer.writeStartDocument("1.0", true); // 开始文档，xml声明
    writer.writeComment(QString::fromLocal8Bit("软件特攻队"));

    writer.writeStartElement("doc");    // 开始子元素<doc>
    // 下面开始写内容
    writer.writeStartElement("courses"); // 开始子元素<courses>
    {
        writer.writeAttribute("count", "4");
        writer.writeAttribute("institution", QString::fromLocal8Bit("软件特攻队"));
        writer.writeAttribute("teacher", QString::fromLocal8Bit("女儿叫老白"));

        // lesson1
        {
            writer.writeStartElement("lesson");
            {
                writer.writeAttribute("url", "https://study.163.com/instructor/1143174933.htm");
                writer.writeAttribute("id", "1");
                writer.writeAttribute("fee", QString::fromLocal8Bit("免费"));
                writer.writeCharacters(QString::fromLocal8Bit("C++老鸟日记"));
           }
            writer.writeEndElement();   // 结束子元素 </lesson>
        }
        // lesson2
        {
            writer.writeStartElement("lesson");
            {
                writer.writeAttribute("url", "https://study.163.com/instructor/1143174933.htm");
                writer.writeAttribute("id", "2");
                writer.writeAttribute("fee", QString::fromLocal8Bit("免费"));
                writer.writeCharacters(QString::fromLocal8Bit("C++跨平台开发中的编译错误"));
            }
            writer.writeEndElement();   // 结束子元素 </lesson>
        }
        // lesson3
        {
            writer.writeStartElement("lesson");
            {
                writer.writeAttribute("url", "https://study.163.com/instructor/1143174933.htm");
                writer.writeAttribute("id", "3");
                writer.writeCharacters(QString::fromLocal8Bit("Qt 5/PyQt 5实战指南（C++版）"));
            }
            writer.writeEndElement();   // 结束子元素 </lesson>
        }
        // lesson4
        {
            writer.writeStartElement("lesson");
            {
                writer.writeAttribute("url", "sorry, not ready");
                writer.writeAttribute("id", "4");
                writer.writeCharacters(QString::fromLocal8Bit("C++跨平台服务模块开发"));
            }
            writer.writeEndElement();   // 结束子元素 </lesson>
        }
    }
    writer.writeEndElement();   // 结束子元素 </courses>
    writer.writeEndElement();   // 结束子元素 </doc>
    writer.writeEndDocument();  // 结束文档

    file.close();
}

/**
* @brief 读取xml格式文件示例代码
*/
void example02() {
    QString strPath =
        ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_19");
    if (!strPath.endsWith("/")) {
        strPath += "/";
    }
    QString strFileName = strPath + "test04_19.xml";
    QFile file(strFileName);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return;
    }

    QXmlStreamReader reader(&file);
    QString strVersion;
    QString strEncoding;
    QXmlStreamReader::TokenType nType = reader.readNext();
    while (!reader.atEnd()) {// 遍历整个文件
        // 读取下一个元素
        nType = reader.tokenType();
        switch (nType) {
        case QXmlStreamReader::StartDocument: { // 文档开始
            qDebug() << QString::fromLocal8Bit("============== 开始文档(XML声明) ===============");
            // XML声明
            strVersion = reader.documentVersion().toString();
            strEncoding = reader.documentEncoding().toString();
            bool bStandalone = reader.isStandaloneDocument();
            qDebug() << QString::fromLocal8Bit("XML版本:%1  XML编码:%2 Standalone=%3")
                .arg(strVersion).arg(strEncoding).arg(bStandalone);
            break;
        }
        case QXmlStreamReader::Comment: {// 注释
            qDebug() << QString::fromLocal8Bit("========== XML 注释 ===========");
            QString strComment = reader.text().toString();
            qDebug()<< strComment << "\r\n";
            break;
        }
        case QXmlStreamReader::ProcessingInstruction: {  // 处理指令
            qDebug() << QString::fromLocal8Bit("============= 处理指令 ============= ");
            QString strProcInstr = reader.processingInstructionData().toString();
            qDebug() << strProcInstr << "\r\n";
            break;
        }
        case QXmlStreamReader::DTD: {   // DTD
            qDebug() << QString::fromLocal8Bit("============= DTD ============= ");
            QString strDTD = reader.text().toString();
            QXmlStreamNotationDeclarations notationDeclarations = reader.notationDeclarations();  // 符号声明
            QXmlStreamEntityDeclarations entityDeclarations = reader.entityDeclarations();  // 实体声明
                                                                                            // DTD 声明
            QString strDTDName = reader.dtdName().toString();
            QString strDTDPublicId = reader.dtdPublicId().toString();  // DTD 公开标识符
            QString strDTDSystemId = reader.dtdSystemId().toString();  // DTD 系统标识符
            qDebug() << QString::fromLocal8Bit("DTD : %1").arg(strDTD);
            qDebug() << QString::fromLocal8Bit("DTD 名称 : %1").arg(strDTDName);
            qDebug() << QString::fromLocal8Bit("DTD 公开标识符 : %1").arg(strDTDPublicId);
            qDebug() << QString::fromLocal8Bit("DTD 系统标识符 : %1").arg(strDTDSystemId);
            qDebug() << "\r\n";

            break;
        }
        case QXmlStreamReader::StartElement: { // 开始元素
            QString strElementName = reader.name().toString();
            if (QString::compare(strElementName, "doc") == 0) { // 根元素doc
                qDebug() << QString::fromLocal8Bit("============== 开始元素<doc> ==============");
                // 处理doc元素及其子元素
                parseDoc(reader);
            }
            break;
        }
        case QXmlStreamReader::EndElement: { // 结束元素 
            QString strElementName = reader.name().toString();
            if (QString::compare(strElementName, "doc") == 0) { // 根元素doc
                qDebug() << QString::fromLocal8Bit("============= 结束元素</doc> ===============");
            }
            break;
        }
        case QXmlStreamReader::EndDocument: { // 文档结束
            qDebug() << QString::fromLocal8Bit("============== 文档结束 ================");
            break;
        }
        default:
            break;
        }
        reader.readNext();
    }
    if (reader.hasError()) {
        // 错误处理,比如输出日志或执行其他操作
    }
    file.close();
}

void parseDoc(QXmlStreamReader& reader) {

    QXmlStreamReader::TokenType nType = reader.readNext();
    while (!reader.atEnd()) {
        nType = reader.tokenType();
        switch (nType) {
        case QXmlStreamReader::StartElement: { // 开始元素
            QString strElementName = reader.name().toString();
            if (QString::compare(strElementName, "courses") == 0) {
                qDebug() << QString::fromLocal8Bit("============== 开始元素<courses> ==============");
                // 处理courses
                parseCourses(reader);
            }
            break;
        }
        case QXmlStreamReader::EndElement: { // 结束元素 
            QString strElementName = reader.name().toString();
            qDebug() << QString::fromLocal8Bit("============= 结束元素<%1> =============").arg(strElementName);
            return;
        }
        default:
            break;
        }
        nType = reader.readNext();
    }
}

void    parseCourses(QXmlStreamReader& reader) {
    QXmlStreamReader::TokenType nType = reader.readNext(); // 将reader指向lesson子元素.
    while (!reader.atEnd()) {
        nType = reader.tokenType();
        switch (nType) {
        case QXmlStreamReader::StartElement: { // 开始元素 
            QString strElementName = reader.name().toString();
            if (QString::compare(strElementName, "lesson") == 0) { // lesson元素
                qDebug() << QString::fromLocal8Bit("============= 开始元素<lesson> =============");
                // 解析lesson
                parseLesson(reader);
                continue;
            }
            break;
        }
        case QXmlStreamReader::EndElement: { // 结束元素 
            QString strElementName = reader.name().toString();
            qDebug() << QString::fromLocal8Bit("============= 结束元素<%1> =============").arg(strElementName);
            if (QString::compare(strElementName, "courses") == 0) { // 结束元素
                return;
            }
            break;
        }
        default:
            break;
        }  
        nType = reader.readNext();
    }
}

void parseLesson(QXmlStreamReader& reader) {
    QXmlStreamReader::TokenType nType;
    QString strElementName;
    QXmlStreamAttributes attributes; 
    QXmlStreamAttributes::iterator iteAttribute;
    QString strText;
    while (!reader.atEnd()) {
        nType = reader.tokenType();
        switch (nType)
        {
        case QXmlStreamReader::StartElement:
            strElementName = reader.name().toString();
            attributes = reader.attributes();
            for (iteAttribute= attributes.begin(); iteAttribute!= attributes.end(); iteAttribute++) {
                qDebug() << (*iteAttribute).name() << "=" << (*iteAttribute).value();
            }
            break;
        case QXmlStreamReader::EndElement:
            strElementName = reader.name().toString();    
            if (strElementName != "lesson") {
                return;
            }
            qDebug() << QString::fromLocal8Bit("============= 结束元素:%1 =============").arg(strElementName); 
            break;
        case QXmlStreamReader::Characters:
            strText = reader.text().toString();
            qDebug() << QString("Characters:%1").arg(strText);
            break;
        default:
            break;
        }  
        nType = reader.readNext();
    }
}
