/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: backlog.h
\brief 演示用头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/11 
*/

#pragma once
#include <QFrame>
#include "ui_backlog.h" // 头文件名称来自: xxx.ui  ---> ui_xxx.h
#include "task.h"


class CWidgetBacklog : public QFrame {
	Q_OBJECT
public:
	CWidgetBacklog(QWidget* parent, const QString& strProjectCode, int backlogId, CWidgetTask::ETaskState eState);
	~CWidgetBacklog(){;}
    /*
     *  @brief 设置id
     *  @param[in] id backlogid 
	 *  @return void
    */
	void setId(int id);
    /*
     *  @brief 获取测试方案
     *  @return 测试方案
    */
	int getId() {
		return m_nId;
	}   
    /*
     *  @brief 设置估计工作量
     *  @param[in] days 估计工作量 
	 *  @return void
    */
	void setEstimateWorkload(int days);
    /*
     *  @brief 获取估计工作量
     *  @return 估计工作量
    */
	int getEstimateWorkload() {
		return m_nEstimateWorkload;
	}   
	/*
     *  @brief 设置backlog
     *  @param[in] str backlog
	 *  @return void
    */
	void setBacklog(const QString& str) {
		m_strBacklog = str;
		ui.pleBacklog->setPlainText(str);
	}
    /*
     *  @brief 获取backlog
     *  @return backlog
    */
	QString getBacklog() {
		return m_strBacklog;
	}
    /*
     *  @brief 设置测试方案
     *  @param[in] str 测试方案
	 *  @return void
    */
	void setHowToTest(const QString& str) {
		m_strHowToTest = str;
	}
    /*
     *  @brief 获取测试方案
     *  @return 测试方案
    */
	QString getHowToTest() {
		return m_strHowToTest;
	}
	/*
	*  @brief 设置backlog所属的项目编号
	*  @param[in] strProjectNo 项目编号
	*  @return void
	*/
	void setProjectCode(const QString& strProjectCode) {
		m_strProjectCode = strProjectCode;
	}
	/*
	*  @brief 获取backlog所属的项目编号
	*  @return 项目编号
	*/
	QString getProjectCode() {
		return m_strProjectCode;
	}
Q_SIGNALS:
	void sig_enter(const QString&);
	void sig_leave(const QString&);
	void sig_pressed(const QString&);
	void sig_saved();
	void sig_taskAdded();
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
	void initialize(); 
private slots:
	void slot_save();
	void slot_addTask();
private:
	Ui::CWidgetBacklog ui;
	QString m_strProjectCode;
	QString m_strBacklog;
	int m_nEstimateWorkload;
	QString m_strHowToTest;
	int m_nId;
	CWidgetTask::ETaskState m_eState;
};

