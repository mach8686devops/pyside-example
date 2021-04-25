/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: customwidget.h
\brief 演示用头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/11 
*/

#pragma once
#include <QFrame>


class CCustomBar : public QFrame {
	Q_OBJECT
public:
	CCustomBar(QWidget* parent);
	~CCustomBar(){;}

    /*
     *  @brief 设置棒图的尺寸数据
	 *  @param[in] min 最小值
	 *  @param[in] max 最大值
	 *  @param[in] value 当前值
	 *  @return void
    */
	void setValue(qreal min, qreal max, qreal value);
Q_SIGNALS:
	void sig_enter(const QString&);
	void sig_leave(const QString&);
protected:
    /*
     *  @brief 重写父类的 paintEvent()
     *  @param[in] event 刷新事件对象指针
    */
    virtual void paintEvent(QPaintEvent *event);
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
private:
	qreal m_dMin;
	qreal m_dMax;
	qreal m_dValue;
};

