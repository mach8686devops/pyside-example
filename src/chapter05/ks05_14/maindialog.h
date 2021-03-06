/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: maindialog.h
\brief  CMainDialog类定义头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#pragma once

#include <QPixmap>

#include "ui_maindialog.h" // 头文件名称来自: maindailog.ui  ---> ui_maindialog.h

QT_BEGIN_NAMESPACE
class QMovie;
QT_END_NAMESPACE

// 父类的名称来自ui文件中对话框的类名：对象查看器中的类名
class CMainDialog : public QDialog {
	Q_OBJECT
public:
	CMainDialog(QWidget* pParent);
	~CMainDialog();

protected:
    virtual void timerEvent(QTimerEvent *event);

private slots:
	void onStartStop();
private:
	
	void initialDialog();
private:
	bool	m_bStart;
	Ui::CMainDialog ui;
	QPixmap	m_png[4];
	QMovie* m_movie;
	int		m_idx;
    int     m_timerId; /// 定时器id
};

