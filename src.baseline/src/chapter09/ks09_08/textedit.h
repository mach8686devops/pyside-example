/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: textedit.h
\brief 演示用头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/8 
*/

#pragma once
#include <QTextEdit>


class CTextEdit : public QTextEdit
{
	Q_OBJECT
public:
	CTextEdit(QWidget* parent);
	~CTextEdit(){;}

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *e) override;

Q_SIGNALS:
	void viewMouseMove(QMouseEvent *event);

private:
};
