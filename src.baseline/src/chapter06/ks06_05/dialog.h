/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.h
\brief 演示用头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/8 
*/

#pragma once

#include "ui_dialog.h"
#include <QDialog>


class CDialog : public QDialog
{
	Q_OBJECT
public:
	CDialog(QWidget* parent);
	~CDialog(){;}
	void openFile(const QString &fileName);

protected:
    /*
     * @brief 初始化界面
    */
	void initialDialog();
private:
    /*
     * @brief 初始化各个子控件
    */
	void initialControls();
    /*
     * @brief 连接信号槽
    */
	void connectSignalsAndSlots();


private slots:
    /*
     * @brief 打开GIF文件槽函数
    */
	void slot_open();
    /*
     * @brief 暂停槽函数
     * @param[in] b true:暂停, false:播放
    */
    void slot_pause(bool b);
    /*
     * @brief 更新按钮的状态。比如按钮的使能状态(enable/disable)
    */
	void slot_updateButtons();
private:
	Ui::CDialog ui;
	QString m_currentDirectory;
	QMovie* m_movie;
};


