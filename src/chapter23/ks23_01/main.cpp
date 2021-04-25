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

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "base/basedll/baseapi.h"

void queryTable(); // 查询数据

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // 创建并打开数据库
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    QString strDir = ns_train::getPath("$TRAINDEVHOME/test/chapter23/ks23_01/");
    QDir dir(strDir);
    if (!dir.exists())
        dir.mkpath(strDir);
    QString strFile = strDir + "data.dbfile";
    database.setDatabaseName(strFile);
	database.setUserName("admin");      // 数据库用户名   
	database.setPassword("admin1235");  // 数据库密码  
    if (!database.open()) {
        qDebug() << "Error: Failed to add database." << database.lastError();
    }
    else {
        qDebug() << "Info: Succeed to add database." ;
    }

    // 创建表
    QSqlQuery sql_query;
    if (!sql_query.exec("create table people(id int primary key, name text, weight int)"))  {
        qDebug() << "Error: Fail to create table."<< sql_query.lastError();
    }
    else {
        qDebug() << "Info: Table created!";
    }

    // 插入数据
    if (!sql_query.exec("insert into people values(1, \"kangxi\", 80)")) {
        qDebug() << "Error: " << sql_query.lastError();
    }
    else {
        qDebug() << "Info: inserted Alex!";
    }
    if (!sql_query.exec("insert into people values(2, \"libai\", 77)")) {
        qDebug() << "Error: " << sql_query.lastError();
    }
    else {
        qDebug() << "Info: inserted Paul!";
    }
    // 查询数据
    queryTable();

    // 批量插入数据
    QStringList names;
    names<<"zhao"<<"qian"<<"sun"<<"li";
    // 为每一列标题添加绑定值
    sql_query.prepare("insert into people (id, name, weight) "
                      "values (:id, :name, :weight)");
    int id = 3;
    //从names表里获取每个名字
    foreach (QString name, names) {
        sql_query.bindValue(":id", id++);   // id
        sql_query.bindValue(":name", name); // 名字
        sql_query.bindValue(":weight", 80 );// weiht，使用默认值
        sql_query.exec();                   // 插入记录
     }

    // 更新数据
    if (!sql_query.exec("update people set name = \"Ben\" where id = 1"))
		qDebug() << sql_query.lastError();
	else
		qDebug() << "Info: updated!";

    // 再次查询数据
    queryTable();

    // 删除数据
    if (!sql_query.exec("delete from people where id = 1"))
		qDebug() << sql_query.lastError();
	else
		qDebug()<<"Info: people deleted!";

    // 删除表
    if (!sql_query.exec("drop table people"))
		qDebug() << sql_query.lastError();
    else
		qDebug() << "table cleared";    

    // 关闭数据库
    database.close();
    return a.exec();
}

void queryTable() {
    QSqlQuery sql_query;
    if (!sql_query.exec("select * from people"))  {
        qDebug()<<sql_query.lastError();
    }
    else {
        int id = 0;
        QString name;
        int weight = 0;
        while(sql_query.next()) {
            id = sql_query.value(0).toInt();
            name = sql_query.value(1).toString();
            weight = sql_query.value(2).toInt();
            qDebug()<<QString("id:%1    name:%2    weight:%3").arg(id).arg(name).arg(weight);
        }
    }
}
