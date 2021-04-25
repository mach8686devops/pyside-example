﻿/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: listwidget.h
\brief 演示用头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/8 
*/

#pragma once
#include <QListWidget>


class CListWidget : public QListWidget
{
//	Q_OBJECT
public:
	/**
	* @brief 构造函数
	* @param[in] parent 日志悬浮窗的父对象
	*/
	CListWidget(QWidget* parent);
	~CListWidget();

public:
	

protected:
	/**
	* @brief 拖拽进入事件响应
	* @param[in] event 拖拽事件
	*/
	void dragEnterEvent(QDragEnterEvent* event);

	/**
	* @brief 拖拽移动事件响应
	* @param[in] event 拖拽事件
	*/
	void dragMoveEvent(QDragMoveEvent* event);

	/**
	* @brief 拖拽离开事件响应
	* @param[in] event 拖拽事件
	*/
	void dragLeaveEvent(QDragLeaveEvent *event);

	/**
	* @brief 拖拽放下事件响应
	* @param[in] event 拖拽事件
	*/
	void dropEvent(QDropEvent *event);

private:
	QString m_strFileName;
};
