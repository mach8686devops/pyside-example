/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: infodialog.h
\brief 演示用头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/8 
*/

#pragma once

#include "ui_logindialog.h"
#include <QDialog>


class CLoginDialog : public QDialog {
	Q_OBJECT
public:
    CLoginDialog(QWidget* parent);
    ~CLoginDialog() {}
	/*
	*  @brief 授权是否有效
	*  @return true:有效，false:无效
	*/	
	bool isAuthorized() {
		return m_bAuthorized;
	}
    /*
     *  @brief 获取登录用户名
     *  @return 用户名
    */	
	QString getUser();

private:
	/*
	*  @brief 授权是否有效
	*  @return true:有效，false:无效
	*/	
	bool varify();
private slots:
	void slot_accept();

private:
    Ui::CLoginDialog  ui;
	bool m_bAuthorized; /// 授权是否有效
};


