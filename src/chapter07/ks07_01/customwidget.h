/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: customwidget.h
\brief 演示用头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/8 
*/
#pragma once
#include <QWidget>

#include "ui_customwidget.h"

class CCustomWidget : public QWidget {
public:
	CCustomWidget(QWidget* parent);
	~CCustomWidget(){;}

protected:
    /*
     *  @brief 重写父类的 resizeEvent()
     *  @param[in] event QResizeEvent对象指针
    */
    virtual void resizeEvent(QResizeEvent *event);
    /*
     *  @brief 重写父类的 paintEvent()
     *  @param[in] event 刷新事件对象指针
    */
    virtual void paintEvent(QPaintEvent *event);
private:
	void initialize();

private:
	Ui::CCustomWidget ui;
	QMovie*	m_movie;
	QLabel* m_transparentLabel;
};

