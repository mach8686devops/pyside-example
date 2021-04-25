/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: infodialog.cpp
\brief	
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9 
*/
#include "logindialog.h"
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include "config.h"


CLoginDialog::CLoginDialog(QWidget* parent)
    : QDialog(parent), m_bAuthorized(false) {
	ui.setupUi(this);

    connect(ui.buttonBox, &QDialogButtonBox::accepted,
            this, &CLoginDialog::slot_accept);
    connect(ui.buttonBox, &QDialogButtonBox::rejected,
            this, &CLoginDialog::reject);

    // 设置密码的echoMode
    ui.lePassword->setEchoMode(QLineEdit::Password);
    ui.lePassword->setPlaceholderText("please input password.");
}

QString CLoginDialog::getUser() {
	return ui.leName->text();
}

void CLoginDialog::slot_accept() {
	if (varify()) {
		QDialog::accept();
	}
	else { 
		QMessageBox::information(this, "login", "invalid password");
	}
}
bool CLoginDialog::varify() {
	m_bAuthorized = false;
 
    QString strId;
    QString strName = ui.leName->text();
	qDebug() << strName;
    QString strPassword;
    QByteArray byteArray;
    QSqlQuery sql_query;
    QString strSql;
    strSql = "select password from users where name = \'";
	strSql += strName;
	strSql += "\'";
    if (sql_query.exec(strSql)) {
        if (sql_query.first()) {
			strPassword = sql_query.value(0).toString();
			qDebug() << strPassword;
			if (strPassword == ui.lePassword->text()) {
				m_bAuthorized = true;
				return true;
			}
        }
    }
	return false;
}