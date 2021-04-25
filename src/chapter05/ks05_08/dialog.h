/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.h
\brief  CDialog 类的定义文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/
#pragma once
#include "ui_dialog.h" // 头文件名称来自: dialog.ui  ---> ui_dialog.h

class CMyObject;

// 父类的名称来自ui文件中对话框的类名：对象查看器中的类名
class CDialog : public QDialog {
	Q_OBJECT
public:
	CDialog(QWidget* pParent);
	~CDialog();

Q_SIGNALS:
    void signal_addressSaved(const QString&); // CDialog的信号

private slots:
	void slot_addressSaved(const QString&);
private:
	void initialDialog();

private:
    Ui::CDialog ui;
};
