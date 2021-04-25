/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: simpledialog.h
\brief  CSimpleDialog类的定义文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#pragma once
#include <QDialog>
#include "ui_simpledialog.h" // 头文件名称来自: simpledialog.ui  ---> ui_simpledialog.h


// 父类的名称来自ui文件中对话框的类名：对象查看器中的类名
class CSimpleDialog : public QDialog
{
	Q_OBJECT
public:
	CSimpleDialog(QWidget* pParent);
	~CSimpleDialog();

private:
    Ui::CSimpleDialog ui;
};
