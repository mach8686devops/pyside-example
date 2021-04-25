/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.h
\brief  CDialog类定义头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#pragma once
#include "ui_dialog.h" // 头文件名称来自: dialog.ui  ---> ui_dialog.h

QT_BEGIN_NAMESPACE
class QEvent;
QT_END_NAMESPACE

class CRecvThread;
class CSendThread;

class CDialog : public QDialog {
	Q_OBJECT
public:
	CDialog(QWidget* pParent);
	~CDialog();

protected:
	virtual void customEvent(QEvent *event);
private slots:
	void slot_startthread();
    void slot_stopthread();
private:
    Ui::CDialog ui;
    CRecvThread* m_pRecvThread;
    CSendThread* m_pSendThread;
};
