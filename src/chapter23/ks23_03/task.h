/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: task.h
\brief 演示用头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/11 
*/

#pragma once
#include <QFrame>
#include "ui_task.h" // 头文件名称来自: xxx.ui  ---> ui_xxx.h


class CWidgetTask : public QFrame {
	Q_OBJECT
public:
	enum ETaskState {
		ETaskState_Todo = 0,
		ETaskState_Doing,
		ETaskState_Finished,
	};
	CWidgetTask(QWidget* parent, int nState);
	~CWidgetTask(){;}
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
	*  @brief 设置task
	*  @param[in] str task
	*  @return void
	*/
	void setTask(const QString& str);
	/*
	*  @brief 获取task
	*  @return task
	*/
	QString getTask() {
		return m_strTask;
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
	/*
	*  @brief 设置backlog Id
	*  @param[in] id backlog Id
	*  @return void
	*/
	void setBacklogId(int id) {
		m_nBacklogId = id;
	}
	/*
	*  @brief 获取backlog Id
	*  @return backlog Id
	*/
	int getBacklogId() {
		return m_nBacklogId;
	}
	/*
	*  @brief 设置开发者
	*  @param[in] strProjectNo 开发者
	*  @return void
	*/
	void setDeveloper(const QString& strDeveloper);
	/*
	*  @brief 获取开发者
	*  @return 开发者
	*/
	QString getDeveloper() {
		return m_strDeveloper;
	}
Q_SIGNALS:
	void sig_refresh();	
	void sig_enter(const QString&);
	void sig_leave(const QString&);
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


private slots:
	void slot_save();
	void slot_accept();
	void slot_finish();
	void slot_back();
private:
	void save();
private:
	Ui::CWidgetTask ui;
	QString m_strProjectCode;
	QString m_strTask;
	int m_nEstimateWorkload;
	int m_nBacklogId;
	int m_nId;
	int m_nState;
	QString m_strDeveloper;
};

