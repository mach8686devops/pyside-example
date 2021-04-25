/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: customlabel.h
\brief 演示用头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/11
*/

#pragma once
#include <QLabel>


class CCustomLabel : public QLabel {
	Q_OBJECT
public:
	CCustomLabel(QWidget* parent);
	~CCustomLabel() { ; }

Q_SIGNALS:
	void sig_enter(const QString&);
	void sig_leave(const QString&);
	void sig_pressed(const QString&);

protected:
	/*
	*  @brief 重写父类的进入事件
	*  @param[in] event 事件对象
	*/
	virtual void enterEvent(QEvent *event);
	/*
	*  @brief 重写父类的退出事件()
	*  @param[in] event 事件对象
	*/
	virtual void leaveEvent(QEvent *event);
	/*
	*  @brief 重写父类的鼠标事件()
	*  @param[in] event 事件对象
	*/
void mousePressEvent(QMouseEvent *event); 
private:
};

