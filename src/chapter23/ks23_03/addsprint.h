/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: addsprint.h
\brief  CWidgetAddSprint 类定义头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/11
*/

#pragma once

#include "ui_addsprint.h" // 头文件名称来自: xxx.ui  ---> ui_xxx.h

// 父类的名称来自ui文件中对话框的类名：对象查看器中的类名
class CWidgetAddSprint : public QWidget {
    Q_OBJECT
public:
	CWidgetAddSprint(QWidget* pParent);
    ~CWidgetAddSprint();
	
	// 清空所有控件的内容
	void clear();
	// 初始化界面
	void initialize();
Q_SIGNALS:
	void sig_getBack();
private slots:
	void slot_save();
private:
	bool m_bModify;
    Ui::CWidgetAddSprint ui;
};
