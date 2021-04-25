/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: user.cpp
\brief  CWidgetUser
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#include "user.h"
#include <QDebug>
#include <QFileDialog>
#include <QSqlError>
#include <QSqlQuery>
#include "base/basedll/baseapi.h"

CWidgetUser::CWidgetUser(QWidget* pParent) : QWidget(pParent) , m_bModify(false) {
	ui.setupUi(this);
    connect(ui.btnSave, &QPushButton::clicked, this, &CWidgetUser::slot_save);
    connect(ui.btnSelectPhoto, &QPushButton::clicked, this, &CWidgetUser::slot_selectphoto);
	connect(ui.btnGetback, &QPushButton::clicked, this, &CWidgetUser::sig_getBack);
}

CWidgetUser::~CWidgetUser() {
	
}

void CWidgetUser::setModifyMode(bool b) {
    m_bModify = b;
    if (b) {
        ui.btnSave->setText(tr("save"));
    }
    else {
        ui.btnSave->setText(tr("add"));
    }
}

void CWidgetUser::clear() {
    ui.leId->setText("");
    ui.leName->setText("");
    ui.lePassword->setText("");
    ui.label_photo->setPixmap(QPixmap());
}
QStringList CWidgetUser::getUsers() {
	QStringList strList;
	
	QString strName;
	QSqlQuery sql_query;
	QString strSql;
	strSql = "select name from users";
	if (sql_query.exec(strSql)) {
		while (sql_query.next()) {
			strName = sql_query.value(0).toString();
			strList << strName;
		}		
	}
	else {
		qDebug() << sql_query.lastError();
	}
	return strList;
}

void CWidgetUser::loadUser(const QString& strUser) {
    
    QString strId;
    int id = 0;
	QString strName;
    QString strPassword;
    QByteArray byteArray;
    QSqlQuery sql_query;
    QString strSql;
	strSql = "select id,name,password,role,photo from users where name = \'";
	strSql += strUser;
	strSql += "\'";
    if (sql_query.exec(strSql)) {
        int role = 0;
        if (sql_query.first()) {
            id = sql_query.value(0).toInt();
            strName = sql_query.value(1).toString();
            strPassword = sql_query.value(2).toString();
            role = sql_query.value(3).toInt();
            byteArray = sql_query.value(4).toByteArray();
        }
        else {
            qDebug() << sql_query.lastError();
        }
    }
    else {
        qDebug() << sql_query.lastError();
    }

    strId = QString("%1").arg(id);
    ui.leId->setText(strId);
	ui.leName->setText(strName);
    ui.lePassword->setText(strPassword);
	qDebug() << "loadUser:password:" << strPassword;
    QPixmap pixmap;
    pixmap.loadFromData(byteArray);
    pixmap = pixmap.scaled(ui.label_photo->width(), ui.label_photo->height());
    ui.label_photo->setPixmap(pixmap);
}

void CWidgetUser::slot_selectphoto() {
    m_strFileName = "";
    QString szDir = ns_train::getDirectory("$TRAINDEVHOME/test/chapter23/ks23_03/");
    //  QString strFilter ("*.txt *.doc");
    QString strFilter("picture(*.png *.jpg)");

#ifdef WIN32
    QString fileName = QFileDialog::getOpenFileName(this, tr("select file to open"), szDir, strFilter);
#else
    QString fileName = QFileDialog::getOpenFileName(this, tr("select file to open"),
        szDir, strFilter, NULL, QFileDialog::DontUseNativeDialog);
#endif
    if (fileName.isEmpty()) {
        return;
    }
    fileName = ns_train::getFileName(fileName);
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        return;
    }
    m_strFileName = fileName;
    QPixmap pixmap(fileName);
    pixmap = pixmap.scaled(ui.label_photo->width(), ui.label_photo->height());
    ui.label_photo->setPixmap(pixmap);
}

void CWidgetUser::slot_save() {
 
    QString strName = ui.leName->text();
    QString strPassword = ui.lePassword->text();
    QByteArray byteArray;
    QFile file(m_strFileName);
    if (file.open(QFile::ReadOnly)) {
        byteArray = file.readAll();
    }
    QSqlQuery sql_query; 
	qDebug() <<"slot_save : password=" << strPassword;
	if (m_bModify)
	{
		QString strSql;
		strSql = "update users set password = :password, photo=:photo where name = \'";
		strSql += strName;
		strSql += "\'";
		sql_query.prepare(strSql);
		sql_query.bindValue(":password", strPassword);// 密码
		sql_query.bindValue(":photo", byteArray); // 照片
	}
	else {
		sql_query.prepare("insert into users (name, password,photo) "
			"values (:name, :password, :photo)");
		sql_query.bindValue(":name", strName); // 名字
		sql_query.bindValue(":password", strPassword);// 密码
		sql_query.bindValue(":photo", byteArray); // 照片
	}
    sql_query.exec();                   // 插入记录
}