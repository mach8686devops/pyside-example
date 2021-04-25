/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: logdockwidget.h
\brief 日志窗口类定义文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/01
*/

#pragma once

#include <QDockWidget>

QT_BEGIN_NAMESPACE
class QTableWidget;
QT_END_NAMESPACE

class  CLogDockWidget : public QDockWidget {
public:
	/**
	* @brief 构造函数
	* @param[in] title	日志悬浮窗的标题
	* @param[in] parent 日志悬浮窗的父对象
	* @param[in] flags	日志悬浮窗的标志
	*/
	CLogDockWidget(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);
	//! 析构函数
	virtual ~CLogDockWidget();
protected:
	/**
	* @brief 在日志悬浮窗中显示日志
	* @param[in] QEvent	日志事件
	*/
	virtual void customEvent(QEvent* e) Q_DECL_OVERRIDE;

private:
	QTableWidget *m_pTableWidget; // 用来显示日志的控件
};